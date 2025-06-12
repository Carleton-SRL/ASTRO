#include "pch.h"
#include "TapMsecPchHeaders.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: ScramnetDll.cpp                                       $
//
// $Revision:: 2                                                     $
//
// $History:: ScramnetDll.cpp                                        $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 1/20/03    Time: 6:34p
//Updated in $/TapMsec
//Add TapMsecPchHeaders.h
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 12/20/02   Time: 4:57p
//Created in $/TapMsec
//Initial development
//
//
//---------------------------------------------------------------------------




#ifndef ScamnetDllH
#include "ScramnetDll.h"
#endif

extern "C" {
#include "Scramnet/scrplus.h"
};

namespace ScramnetDllNamespace
{
//---------------------------------------------------------------------------
static const AnsiString ScramnetDllName = ( "PnpScr.dll" );



//---------------------------------------------------------------------------
static const AnsiString    Name_FindCSRSet                    ( "_FindCSRSet@0" );
static const AnsiString    Name_GetApp0MemPtr                 ( "_GetApp0MemPtr@0" );
static const AnsiString    Name_GetApp1MemPtr                 ( "_GetApp1MemPtr@0" );
static const AnsiString    Name_GetBIOSInfo                   ( "_GetBIOSInfo@0" );
static const AnsiString    Name_GetBIOSVersion                ( "_GetBIOSVersion@0" );
static const AnsiString    Name_GetScrTransactionType         ( "_GetScrTransactionType@0" );
static const AnsiString    Name_GetSysVersion                 ( "_GetSysVersion@0" );
static const AnsiString    Name_PciIsrCallback                ( "_PciIsrCallback@4" );
static const AnsiString    Name_ReadSCRByte                   ( "_ReadSCRByte@8" );
static const AnsiString    Name_ReadSCRLong                   ( "_ReadSCRLong@8" );
static const AnsiString    Name_ReadSCRWord                   ( "_ReadSCRWord@8" );
static const AnsiString    Name_ScrConfigured                 ( "_ScrConfigured@0" );
static const AnsiString    Name_ScrFound                      ( "_ScrFound@0" );
static const AnsiString    Name_SetScrTransactionType         ( "_SetScrTransactionType@4" );
static const AnsiString    Name_WriteSCRByte                  ( "_WriteSCRByte@8" );
static const AnsiString    Name_WriteSCRLong                  ( "_WriteSCRLong@8" );
static const AnsiString    Name_WriteSCRWord                  ( "_WriteSCRWord@8" );


static const AnsiString    Name_get_base_mem                  ( "_get_base_mem@0" );
static const AnsiString    Name_get_scr_node_id               ( "_get_scr_node_id@0" );
static const AnsiString    Name_get_scr_phy_csr_addr          ( "_get_scr_phy_csr_addr@0" );
static const AnsiString    Name_get_scr_phy_mem_addr          ( "_get_scr_phy_mem_addr@0" );
static const AnsiString    Name_get_scr_time_out              ( "_get_scr_time_out@0" );
static const AnsiString    Name_get_scr_user_mem_size         ( "_get_scr_user_mem_size@0" );
static const AnsiString    Name_scr_acr_mm                    ( "_scr_acr_mm@4" );
static const AnsiString    Name_scr_acr_read                  ( "_scr_acr_read@4" );
static const AnsiString    Name_scr_acr_write                 ( "_scr_acr_write@8" );
static const AnsiString    Name_scr_board_status              ( "_scr_board_status@4" );
static const AnsiString    Name_scr_brd_select                ( "_scr_brd_select@4" );
static const AnsiString    Name_scr_bswp_mm                   ( "_scr_bswp_mm@0" );
static const AnsiString    Name_scr_byte_mem_exist            ( "_scr_byte_mem_exist@4" );
static const AnsiString    Name_scr_csr_read                  ( "_scr_csr_read@4" );
static const AnsiString    Name_scr_csr_write                 ( "_scr_csr_write@8" );
static const AnsiString    Name_scr_delay                     ( "_scr_delay@4" );
static const AnsiString    Name_scr_dfltr_mm                  ( "_scr_dfltr_mm@4" );
static const AnsiString    Name_scr_dma_read                  ( "_scr_dma_read@12" );
static const AnsiString    Name_scr_dma_write                 ( "_scr_dma_write@12" );
static const AnsiString    Name_scr_error_mm                  ( "_scr_error_mm@8" );
static const AnsiString    Name_scr_fifo_mm                   ( "_scr_fifo_mm@8" );
static const AnsiString    Name_scr_fswin_mm                  ( "_scr_fswin_mm@0" );
static const AnsiString    Name_scr_id_mm                     ( "_scr_id_mm@8" );
static const AnsiString    Name_scr_int_mm                    ( "_scr_int_mm@8" );
static const AnsiString    Name_scr_lnk_mm                    ( "_scr_lnk_mm@4" );
static const AnsiString    Name_scr_load_mm                   ( "_scr_load_mm@8" );
static const AnsiString    Name_scr_long_mem_exist            ( "_scr_long_mem_exist@4" );
static const AnsiString    Name_scr_mclr_mm                   ( "_scr_mclr_mm@4" );
static const AnsiString    Name_scr_mem_mm                    ( "_scr_mem_mm@4" );
static const AnsiString    Name_scr_probe_mm                  ( "_scr_probe_mm@8" );
static const AnsiString    Name_scr_read_int_fifo             ( "_scr_read_int_fifo@4" );
static const AnsiString    Name_scr_reg_mm                    ( "_scr_reg_mm@4" );
static const AnsiString    Name_scr_reset_mm                  ( "_scr_reset_mm@0" );
static const AnsiString    Name_scr_rw_mm                     ( "_scr_rw_mm@4" );
static const AnsiString    Name_scr_save_mm                   ( "_scr_save_mm@8" );
static const AnsiString    Name_scr_short_mem_exist           ( "_scr_short_mem_exist@4" );
static const AnsiString    Name_scr_smem_mm                   ( "_scr_smem_mm@8" );
static const AnsiString    Name_scr_wml_mm                    ( "_scr_wml_mm@4" );
static const AnsiString    Name_sp_bist_rd                    ( "_sp_bist_rd@4" );
static const AnsiString    Name_sp_cfg_read                   ( "_sp_cfg_read@4" );
static const AnsiString    Name_sp_gtm_mm                     ( "_sp_gtm_mm@0" );
static const AnsiString    Name_sp_mem_size                   ( "_sp_mem_size@0" );
static const AnsiString    Name_sp_msg_life                   ( "_sp_msg_life@4" );
static const AnsiString    Name_sp_net_to                     ( "_sp_net_to@4" );
static const AnsiString    Name_sp_plus_find                  ( "_sp_plus_find@0" );
static const AnsiString    Name_sp_protocol                   ( "_sp_protocol@4" );
static const AnsiString    Name_sp_rx_id                      ( "_sp_rx_id@4" );
static const AnsiString    Name_sp_scram_init                 ( "_sp_scram_init@0" );
static const AnsiString    Name_sp_set_cntr                   ( "_sp_set_cntr@4" );
static const AnsiString    Name_sp_set_sm_addr                ( "_sp_set_sm_addr@4" );
static const AnsiString    Name_sp_set_vp                     ( "_sp_set_vp@8" );
static const AnsiString    Name_sp_stm_mm                     ( "_sp_stm_mm@4" );
static const AnsiString    Name_sp_txrx_id                    ( "_sp_txrx_id@4" );
static const AnsiString    Name_sw_cfg_fill                   ( "_sw_cfg_fill@4" );
static const AnsiString    Name_sw_get_int                    ( "_sw_get_int@0" );
static const AnsiString    Name_sw_int_connect                ( "_sw_int_connect@0" );
static const AnsiString    Name_sw_int_disconnect             ( "_sw_int_disconnect@0" );
static const AnsiString    Name_sw_int_snapicon               ( "_sw_int_snapicon@0" );
static const AnsiString    Name_sw_int_snapidis               ( "_sw_int_snapidis@0" );
static const AnsiString    Name_sw_mem_addr                   ( "_sw_mem_addr@0" );
static const AnsiString    Name_sw_net_to                     ( "_sw_net_to@0" );
static const AnsiString    Name_sw_reg_addr                   ( "_sw_reg_addr@0" );
static const AnsiString    Name_sw_set_int                    ( "_sw_set_int@4" );
static const AnsiString    Name_sw_set_size                   ( "_sw_set_size@4" );
static const AnsiString    Name_sw_user_size                  ( "_sw_user_size@0" );

};


#pragma package(smart_init)

using namespace ScramnetDllNamespace;

TScramnetDll::TScramnetDll
   (
   ) :
   Dll( NULL )
{

   Dll                     = LoadLibrary( ScramnetDllName.c_str() );

   if ( !Dll )
   {
      throw( Exception( "Error loading Scramnet DLL PnpScr.dll" ) );
   }


   get_base_mem            = ( get_base_mem_Type                     * ) GetProcAddress( Dll, Name_get_base_mem.c_str() );
   get_scr_node_id         = ( get_scr_node_id_Type                  * ) GetProcAddress( Dll, Name_get_scr_node_id.c_str() );
   get_scr_phy_csr_addr    = ( get_scr_phy_csr_addr_Type             * ) GetProcAddress( Dll, Name_get_scr_phy_csr_addr.c_str() );
   get_scr_phy_mem_addr    = ( get_scr_phy_mem_addr_Type             * ) GetProcAddress( Dll, Name_get_scr_phy_mem_addr.c_str() );
   get_scr_time_out        = ( get_scr_time_out_Type                 * ) GetProcAddress( Dll, Name_get_scr_time_out.c_str() );
   get_scr_user_mem_size   = ( get_scr_user_mem_size_Type            * ) GetProcAddress( Dll, Name_get_scr_user_mem_size.c_str() );
   scr_acr_mm              = ( scr_acr_mm_Type                       * ) GetProcAddress( Dll, Name_scr_acr_mm.c_str() );
   scr_acr_read            = ( scr_acr_read_Type                     * ) GetProcAddress( Dll, Name_scr_acr_read.c_str() );
   scr_acr_write           = ( scr_acr_write_Type                    * ) GetProcAddress( Dll, Name_scr_acr_write.c_str() );
   scr_board_status        = ( scr_board_status_Type                 * ) GetProcAddress( Dll, Name_scr_board_status.c_str() );
   scr_brd_select          = ( scr_brd_select_Type                   * ) GetProcAddress( Dll, Name_scr_brd_select.c_str() );
   scr_bswp_mm             = ( scr_bswp_mm_Type                      * ) GetProcAddress( Dll, Name_scr_bswp_mm.c_str() );
   scr_byte_mem_exist      = ( scr_byte_mem_exist_Type               * ) GetProcAddress( Dll, Name_scr_byte_mem_exist.c_str() );
   scr_csr_write           = ( scr_csr_write_Type                    * ) GetProcAddress( Dll, Name_scr_csr_write.c_str() );
   scr_delay               = ( scr_delay_Type                        * ) GetProcAddress( Dll, Name_scr_delay.c_str() );
   scr_dfltr_mm            = ( scr_dfltr_mm_Type                     * ) GetProcAddress( Dll, Name_scr_dfltr_mm.c_str() );
   scr_dma_read            = ( scr_dma_read_Type                     * ) GetProcAddress( Dll, Name_scr_dma_read.c_str() );
   scr_dma_write           = ( scr_dma_write_Type                    * ) GetProcAddress( Dll, Name_scr_dma_write.c_str() );
   scr_error_mm            = ( scr_error_mm_Type                     * ) GetProcAddress( Dll, Name_scr_error_mm.c_str() );
   scr_fifo_mm             = ( scr_fifo_mm_Type                      * ) GetProcAddress( Dll, Name_scr_fifo_mm.c_str() );
   scr_fswin_mm            = ( scr_fswin_mm_Type                     * ) GetProcAddress( Dll, Name_scr_fswin_mm.c_str() );
   scr_id_mm               = ( scr_id_mm_Type                        * ) GetProcAddress( Dll, Name_scr_id_mm.c_str() );
   scr_int_mm              = ( scr_int_mm_Type                       * ) GetProcAddress( Dll, Name_scr_int_mm.c_str() );
   scr_lnk_mm              = ( scr_lnk_mm_Type                       * ) GetProcAddress( Dll, Name_scr_lnk_mm.c_str() );
   scr_load_mm             = ( scr_load_mm_Type                      * ) GetProcAddress( Dll, Name_scr_load_mm.c_str() );
   scr_long_mem_exist      = ( scr_long_mem_exist_Type               * ) GetProcAddress( Dll, Name_scr_long_mem_exist.c_str() );
   scr_mclr_mm             = ( scr_mclr_mm_Type                      * ) GetProcAddress( Dll, Name_scr_mclr_mm.c_str() );
   scr_mem_mm              = ( scr_mem_mm_Type                       * ) GetProcAddress( Dll, Name_scr_mem_mm.c_str() );
   scr_probe_mm            = ( scr_probe_mm_Type                     * ) GetProcAddress( Dll, Name_scr_probe_mm.c_str() );
   scr_read_int_fifo       = ( scr_read_int_fifo_Type                * ) GetProcAddress( Dll, Name_scr_read_int_fifo.c_str() );
   scr_reg_mm              = ( scr_reg_mm_Type                       * ) GetProcAddress( Dll, Name_scr_reg_mm.c_str() );
   scr_reset_mm            = ( scr_reset_mm_Type                     * ) GetProcAddress( Dll, Name_scr_reset_mm.c_str() );
   scr_rw_mm               = ( scr_rw_mm_Type                        * ) GetProcAddress( Dll, Name_scr_rw_mm.c_str() );
   scr_save_mm             = ( scr_save_mm_Type                      * ) GetProcAddress( Dll, Name_scr_save_mm.c_str() );
   scr_short_mem_exist     = ( scr_short_mem_exist_Type              * ) GetProcAddress( Dll, Name_scr_short_mem_exist.c_str() );
   scr_smem_mm             = ( scr_smem_mm_Type                      * ) GetProcAddress( Dll, Name_scr_smem_mm.c_str() );
   scr_wml_mm              = ( scr_wml_mm_Type                       * ) GetProcAddress( Dll, Name_scr_wml_mm.c_str() );
   sp_bist_rd              = ( sp_bist_rd_Type                       * ) GetProcAddress( Dll, Name_sp_bist_rd.c_str() );
   sp_cfg_read             = ( sp_cfg_read_Type                      * ) GetProcAddress( Dll, Name_sp_cfg_read.c_str() );
   sp_gtm_mm               = ( sp_gtm_mm_Type                        * ) GetProcAddress( Dll, Name_sp_gtm_mm.c_str() );
   sp_mem_size             = ( sp_mem_size_Type                      * ) GetProcAddress( Dll, Name_sp_mem_size.c_str() );
   sp_msg_life             = ( sp_msg_life_Type                      * ) GetProcAddress( Dll, Name_sp_msg_life.c_str() );
   sp_net_to               = ( sp_net_to_Type                        * ) GetProcAddress( Dll, Name_sp_net_to.c_str() );
   sp_plus_find            = ( sp_plus_find_Type                     * ) GetProcAddress( Dll, Name_sp_plus_find.c_str() );
   sp_protocol             = ( sp_protocol_Type                      * ) GetProcAddress( Dll, Name_sp_protocol.c_str() );
   sp_rx_id                = ( sp_rx_id_Type                         * ) GetProcAddress( Dll, Name_sp_rx_id.c_str() );
   sp_scram_init           = ( sp_scram_init_Type                    * ) GetProcAddress( Dll, Name_sp_scram_init.c_str() );
   sp_set_cntr             = ( sp_set_cntr_Type                      * ) GetProcAddress( Dll, Name_sp_set_cntr.c_str() );
   sp_set_sm_addr          = ( sp_set_sm_addr_Type                   * ) GetProcAddress( Dll, Name_sp_set_sm_addr.c_str() );
   sp_set_vp               = ( sp_set_vp_Type                        * ) GetProcAddress( Dll, Name_sp_set_vp.c_str() );
   sp_stm_mm               = ( sp_stm_mm_Type                        * ) GetProcAddress( Dll, Name_sp_stm_mm.c_str() );
   sp_txrx_id              = ( sp_txrx_id_Type                       * ) GetProcAddress( Dll, Name_sp_txrx_id.c_str() );
   sw_cfg_fill             = ( sw_cfg_fill_Type                      * ) GetProcAddress( Dll, Name_sw_cfg_fill.c_str() );
   sw_get_int              = ( sw_get_int_Type                       * ) GetProcAddress( Dll, Name_sw_get_int.c_str() );
   sw_int_connect          = ( sw_int_connect_Type                   * ) GetProcAddress( Dll, Name_sw_int_connect.c_str() );
   sw_int_disconnect       = ( sw_int_disconnect_Type                * ) GetProcAddress( Dll, Name_sw_int_disconnect.c_str() );
   sw_int_snapicon         = ( sw_int_snapicon_Type                  * ) GetProcAddress( Dll, Name_sw_int_snapicon.c_str() );
   sw_int_snapidis         = ( sw_int_snapidis_Type                  * ) GetProcAddress( Dll, Name_sw_int_snapidis.c_str() );
   sw_mem_addr             = ( sw_mem_addr_Type                      * ) GetProcAddress( Dll, Name_sw_mem_addr.c_str() );
   sw_net_to               = ( sw_net_to_Type                        * ) GetProcAddress( Dll, Name_sw_net_to.c_str() );
   sw_reg_addr             = ( sw_reg_addr_Type                      * ) GetProcAddress( Dll, Name_sw_reg_addr.c_str() );
   sw_set_int              = ( sw_set_int_Type                       * ) GetProcAddress( Dll, Name_sw_set_int.c_str() );
   sw_set_size             = ( sw_set_size_Type                      * ) GetProcAddress( Dll, Name_sw_set_size.c_str() );
   sw_user_size            = ( sw_user_size_Type                     * ) GetProcAddress( Dll, Name_sw_user_size.c_str() );


}

TScramnetDll::~TScramnetDll
   (
   )
{
   FreeLibrary( Dll );
}   
