////////////////////////////////////////////////////////////////////////////////
//
// Filename:	zipmmu_tb.cpp
//
// Project:	Zip CPU -- a small, lightweight, RISC CPU soft core
//
// Purpose:	A quick test bench to determine if the zipmmu module works.
//		This test bench does nothing to determine whether or not it
//	is connected properly, but only tests whether or not the zipmmu works
//	as it is supposed to.
//
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015-2016, Gisselquist Technology, LLC
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#include <stdio.h>

#include <verilated.h>
#include <verilated_vcd_c.h>
#include "testb.h"
#include "Vaxi_lite_slave.h"



vluint64_t main_time = 0;       // Current simulation time
 // This is a 64-bit integer to reduce wrap over issues and
 // allow modulus.  You can also use a double, if you wish.

  double sc_time_stamp ()
{       // Called by $time in Verilog
       return main_time;           // converts to double, to match
                                              // what SystemC does
 }

class	AXILITEMASTER_TB : public TESTB<Vaxi_lite_slave> 

{

	long		m_tickcount;
	bool		m_err, m_debug;
public:

	AXILITEMASTER_TB(void) {
		m_debug = true;
	}

#define	v__DOT__mem_stb	v__DOT__mut__DOT__r_valid
	void	tick(void) {

		TESTB<Vaxi_lite_slave>::tick(); //calling tick() in tb.h
	}

	void reset(void) {
		m_core->S_AXI_ARESETN    = 0;
		//m_core->i_ctrl_cyc_stb = 0;
		//m_core->i_wbm_cyc  = 0;
		//m_core->i_wbm_stb  = 0;
		tick();
		m_core->S_AXI_ARESETN  = 1;
	}

	
	unsigned axi_write(unsigned waddr, unsigned wval) 
	{
		
		////int			errcount = 0;
		unsigned	wresp;

		//write adddress channel handshake
	    m_core->S_AXI_AWVALID = 1;
	    m_core->S_AXI_AWADDR =waddr;    //example write address
	 	m_core->S_AXI_AWPROT = 0;

	    //write data channel handshake
	    m_core->S_AXI_WVALID = 1;
	    m_core->S_AXI_WDATA = wval;    //example write data
	 	m_core->S_AXI_WSTRB = 15;

	    //write response channel handshake
	    m_core->S_AXI_BREADY = 1;
	   
	    unsigned int readys_read = 0;
	    while(readys_read != 3)
	     {
	        if (m_core->S_AXI_AWREADY && m_core->S_AXI_WREADY)
	        {   readys_read = 3;
	            tick();
	            m_core->S_AXI_AWVALID = m_core->S_AXI_WVALID = 0;
	        }
	        else if (m_core->S_AXI_AWREADY)
	        {
	            readys_read |= 1;
	            tick();
	            m_core->S_AXI_AWVALID = 0;
	        }
	        else if (m_core->S_AXI_WREADY)
	        {   readys_read |= 2;
	            tick();
	            m_core->S_AXI_WVALID = 0;
	        }
	        else tick();
	    }
	 /*
	    //master clears S_AXI_WVALID
	    m_core->S_AXI_AWVALID = 0;
	 
	    //master clears S_AXI_WVALID
	    m_core->S_AXI_WVALID = 0;
	 */
	    //wait for slave to indicate it has valid write response
	    while(!m_core->S_AXI_BVALID)
	    {
	        tick();
	    }
	   
	    wresp = m_core->S_AXI_BRESP;
	    printf("AXI Lite Write Response = %d\n",wresp);
	    //master clears bready
	    tick();
	    m_core->S_AXI_BREADY = 0;     
	    tick();

	    return wresp;
	}
 
	unsigned axi_read(unsigned a) 
	{
		unsigned rdata;
		unsigned rresp;

		//read control channel handshake
	    m_core->S_AXI_ARVALID = 1;
	    m_core->S_AXI_ARADDR = 0xa;    //example read address
	 	m_core->S_AXI_ARPROT = 0;
	    //read data channel handshake
	    m_core->S_AXI_RREADY = 1;

	    while(!m_core -> S_AXI_ARREADY)
	    {
	    	tick();
	    }
	 	tick();  //for the case S_AXI_ARREADY comes before S_AXI_ARVALID
	 	m_core -> S_AXI_ARVALID = 0;

	 	while(!m_core -> S_AXI_RVALID)
	 	{

	 		tick();
	 	}
	 	tick();
	 	//m_core -> S_AXI_RREADY = 0;
	  /* 
	    int readys_read = 0;
	    while(readys_read != 3)
	     {
	        if (m_core->S_AXI_ARREADY && m_core->S_AXI_RVALID)
	        {   readys_read = 3;
	            tick();
	            m_core->S_AXI_ARVALID = m_core->S_AXI_RREADY = 0;
	        }
	        else if (m_core->S_AXI_ARREADY)
	        {
	            readys_read |= 1;
	            tick();
	            m_core->S_AXI_ARVALID = 0;
	        }
	        else if (m_core->S_AXI_RVALID)
	        {   readys_read |= 2;
	            tick();
	            m_core->S_AXI_RREADY = 0;
	        }
	        else tick();
	    }
	 */
	    rdata = m_core->S_AXI_RDATA;
	    rresp = m_core->S_AXI_RRESP;
	    printf("AXI Lite Read reponse = %d\n",rresp);
	    //master clears rready
	    m_core->S_AXI_RREADY = 0;

	    return rdata;
	}


}; //end of AXILITEMASTER_TB class


int main(int  argc, char **argv) 
{
	Verilated::commandArgs(argc, argv);

	AXILITEMASTER_TB	*tb = new AXILITEMASTER_TB;
	//unsigned 	*rdbuf; // *mbuf;
	//unsigned	mlen = (1<<LGMEMSIZE), c, blen;
	tb->opentrace("axi_tb.vcd");
	/*
	#ifdef VCD_DUMP
	   	   Verilated::traceEverOn(true);
           VL_PRINTF("Enabling waves...\n");
           VerilatedVcdC* tfp = new VerilatedVcdC;
           tb->trace (tfp, 99);
           tfp->open ("simx.vcd");
 	#endif
	*/

	tb->tick();
	tb->reset();
	tb->tick();

	unsigned waddr = 10;
	unsigned wval = 31;
	unsigned wresp;
	unsigned rdata;


	while (main_time < 50)
    {
		wresp = tb->axi_write(waddr,wval);
		printf("Time=%2d, AXI Lite Write Response = %d\n",main_time,wresp);
		tb->tick();

		rdata = tb->axi_read(waddr);
		printf("Time=%2d, Read data = %d\n",main_time,rdata );

		main_time++;
	}

	 printf("\n Test Done\n");
    // tb->final();               // Done simulating
	 
	 /*#ifdef VCD_DUMP
            tfp->close();
	 #endif
	 */
	             //    // (Though this example doesn't get here)
     delete tb;

	/*tb->opentrace("axi_tb.vcd");
	printf("SUCCESS!!\n");
	exit(0);
	*/
/*
	test_failure:		//label
	printf("FAIL-HERE\n");
	for(int i=0; i<4; i++)
		tb->tick();
	printf("TEST FAILED\n");
	exit(-1);
	*/
}
