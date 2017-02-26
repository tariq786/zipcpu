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
/****		m_core->eval();
		m_core->i_clk = 1;

		bool	writeout = true;

		if ((m_debug)&&(writeout)) {
			printf("%08lx-MMU: ", m_tickcount);
			printf("(%s%s%s%s) %08x (%s%s%s)%08x%s %s %08x/%08x %s%s%s%s%s",
				(m_core->i_ctrl_cyc_stb)?"CT":"  ",
				(m_core->i_wbm_cyc)?"CYC":"   ",
				(m_core->i_wbm_stb)?"STB":"   ",
				(m_core->i_wb_we)?"WE":"  ",
				(m_core->i_wb_addr),
				(m_core->v__DOT__mem_cyc)?"CYC":"   ",
				(m_core->v__DOT__mem_stb)?"STB":"   ",
#define	v__DOT__mem_we	v__DOT__mut__DOT__r_we
				(m_core->v__DOT__mem_we)?"WE":"  ",
				(m_core->v__DOT__mem_addr),
				(m_core->v__DOT__mem_err)?"ER":"  ",
				(m_core->i_wb_we)?"<-":"->",
				(m_core->i_wb_we)?m_core->i_wb_data:m_core->o_rtn_data,
				(m_core->v__DOT__mem_we)?m_core->v__DOT__mut__DOT__r_data:m_core->v__DOT__mem_odata,
				(m_core->o_rtn_stall)?"STALL":"     ",
				(m_core->v__DOT__mut__DOT__setup_ack)?"S":" ",
				(m_core->o_rtn_ack )?"ACK":"   ",
				(m_core->o_rtn_miss)?"MISS":"    ",
				(m_core->o_rtn_err )?"ERR":"   ");

			printf("[%d,%d]",
				m_core->v__DOT__mut__DOT__wr_vtable,
				m_core->v__DOT__mut__DOT__wr_ptable);
			printf("[%d,%d,%04x]",
				m_core->v__DOT__mut__DOT__wr_control,
				m_core->v__DOT__mut__DOT__z_context,
				m_core->v__DOT__mut__DOT__r_context_word);
		***/	/*
			printf("[%08x,%08x-%08x]", 
				m_core->v__DOT__mut__DOT__w_vtable_reg,
				m_core->v__DOT__mut__DOT__w_ptable_reg,
				m_core->v__DOT__mut__DOT__setup_data);
			*/
		/***	printf(" %s[%s%s@%08x,%08x]",
				(m_core->v__DOT__mut__DOT__r_pending)?"R":" ",
				(m_core->v__DOT__mut__DOT__r_we)?"W":" ",
				(m_core->v__DOT__mut__DOT__r_valid)?"V":" ",
				(m_core->v__DOT__mut__DOT__r_addr),
				(m_core->v__DOT__mut__DOT__r_data));
			printf("@%2x[%s%s%s][%s%s%s%s]",
				(m_core->v__DOT__mut__DOT__s_tlb_addr),
				(m_core->v__DOT__mut__DOT__s_pending)?"P":" ",
				(m_core->v__DOT__mut__DOT__s_tlb_hit)?"HT":"  ",
				(m_core->v__DOT__mut__DOT__s_tlb_miss)?"MS":"  ",
				(m_core->v__DOT__mut__DOT__ro_flag)?"RO":"  ",
				(m_core->v__DOT__mut__DOT__simple_miss)?"SM":"  ",
				(m_core->v__DOT__mut__DOT__ro_miss)?"RM":"  ",
				(m_core->v__DOT__mut__DOT__table_err)?"TE":"  ");
				//(m_core->v__DOT__mut__DOT__cachable)?"CH":"  ");
		***/	/*
			printf(" M[%016lx]",
				m_core->v__DOT__mut__DOT__r_tlb_match);
			printf(" P[%3d] = 0x%08x, V=0x%08x, C=0x%08x, CTXT=%04x",
				m_last_tlb_index,
				m_core->v__DOT__mut__DOT__tlb_pdata[m_last_tlb_index],
				m_core->v__DOT__mut__DOT__tlb_vdata[m_last_tlb_index],
				m_core->v__DOT__mut__DOT__tlb_cdata[m_last_tlb_index],
				m_core->v__DOT__mut__DOT__r_context_word);
			*/
		////	printf("\n");
		/////}

		m_core->eval();
	//	m_core->S_AXI_ACLK = 0;
		m_core->eval();

		m_tickcount++;
	}

	void reset(void) {
		m_core->S_AXI_ARESETN    = 0;
		//m_core->i_ctrl_cyc_stb = 0;
		//m_core->i_wbm_cyc  = 0;
		//m_core->i_wbm_stb  = 0;
		tick();
		m_core->S_AXI_ARESETN  = 1;
	}

	/*void wb_tick(void) {
		m_core->i_rst  = 0;
		m_core->i_ctrl_cyc_stb = 0;
		m_core->i_wbm_cyc  = 0;
		m_core->i_wbm_stb  = 0;
		tick();
		assert(!m_core->o_rtn_ack);
		assert(!m_core->o_rtn_err);
	} */


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
	 	m_core->S_AXI_WSTRB = 0;

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
	 
	    //master clears aS_AXI_WVALID
	    m_core->S_AXI_AWVALID = 0;
	 
	    //master clears S_AXI_WVALID
	    m_core->S_AXI_WVALID = 0;
	 
	    //wait for slave to indicate it has valid write response
	    while(!m_core->S_AXI_BVALID)
	    {
	        tick();
	    }
	   
	    wresp = m_core->S_AXI_BRESP;
	    printf("AXI Lite Write Response = %d\n",wresp);
	    //master clears bready
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
	 
	    rdata = m_core->S_AXI_RDATA;
	    rresp = m_core->S_AXI_RRESP;
	    printf("AXI Lite Read reponse = %d\n",rresp);
	    //master clears rready
	    m_core->S_AXI_RREADY = 0;

	    return rdata;
	}


//	bool	debug(void) const { return m_debug; }
//	bool	debug(bool nxtv) { return m_debug = m_core->S_AXI_RDATA;}


}; //end of AXILITEMASTER_TB class


int main(int  argc, char **argv) 
{
	Verilated::commandArgs(argc, argv);

	AXILITEMASTER_TB	*tb = new AXILITEMASTER_TB;
	//unsigned 	*rdbuf; // *mbuf;
	//unsigned	mlen = (1<<LGMEMSIZE), c, blen;

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
	unsigned wval = 15;
	unsigned wresp;
	unsigned rdata;


	while (main_time < 500)
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
