//---------------------------------------------------------------------------

#ifndef ScramnetDllH
#define ScramnetDllH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: ScramnetDll.h                                         $
//
// $Revision:: 2                                                     $
//
// $History:: ScramnetDll.h                                          $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 1/21/03    Time: 10:01a
//Updated in $/TapMsec
//Added path to scramnet include file.
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 12/20/02   Time: 4:57p
//Created in $/TapMsec
//Initial development
//
//
//---------------------------------------------------------------------------


extern "C" {
#include "scramnet/scrplus.h"
};

//---------------------------------------------------------------------------
//
// The following typedefs correspond to the functions defined in the
// SCRAMNet DLL PnpScr.dll.  The function declarations are located in
// scrproto.h.  Using IMPLIB from the command line, one can create a static
// library and reference the functions directly without any problem.  However,
// using the static version would require that every simulator have the PnpScr.dll
// DLL installed on it.  Static linking causes LoadLibrary for the DLL to be called
// whether and DLL functions are called or not.  Therefore dynamic linking is used
// and all the functions defined in scrproto.h are initialized.  Several functions
// that are exported by the DLL are not used here.
//
//    FindCSRSet                    = _FindCSRSet@0
//    GetApp0MemPtr                 = _GetApp0MemPtr@0
//    GetApp1MemPtr                 = _GetApp1MemPtr@0
//    GetBIOSInfo                   = _GetBIOSInfo@0
//    GetBIOSVersion                = _GetBIOSVersion@0
//    GetScrTransactionType         = _GetScrTransactionType@0
//    GetSysVersion                 = _GetSysVersion@0
//    PciIsrCallback                = _PciIsrCallback@4
//    ReadSCRByte                   = _ReadSCRByte@8
//    ReadSCRLong                   = _ReadSCRLong@8
//    ReadSCRWord                   = _ReadSCRWord@8
//    ScrConfigured                 = _ScrConfigured@0
//    ScrFound                      = _ScrFound@0
//    SetScrTransactionType         = _SetScrTransactionType@4
//    WriteSCRByte                  = _WriteSCRByte@8
//    WriteSCRLong                  = _WriteSCRLong@8
//    WriteSCRWord                  = _WriteSCRWord@8
//
//---------------------------------------------------------------------------


typedef    DLL_DEF SCR_INT CALL_CONV scr_long_mem_exist_Type( SCR_LONG_PTR mem_ptr );
    // Determines if long word memory location is valid.

typedef DLL_DEF SCR_INT CALL_CONV scr_short_mem_exist_Type( SCR_SHORT_PTR mem_ptr );
    // Determines if short word memory location is valid.

typedef DLL_DEF SCR_INT CALL_CONV scr_byte_mem_exist_Type( SCR_BYTE_PTR mem_ptr );
    // Determines if byte memory location is valid.

typedef DLL_DEF SCR_INT CALL_CONV sp_scram_init_Type( void );
    // Initialize the board by reading values from ini file, mapping SCRAMNet
    // Registers, mapping SCRAMNet memory, and setting node ID and timeout
    // values equal to the values specifed in the Registry.

typedef DLL_DEF SCR_LONG_PTR CALL_CONV get_base_mem_Type( void );
    // Return a virtual pointer to a block of memory mapped into the SCRAMNet
    // cards physical address space.

typedef DLL_DEF BOOL CALL_CONV SetScrTransactionType_Type( BYTE mode );
    // This function configures the SCRAMNet Card to swap the values read from
    // memory according the paramater passed to the function.
    // **************************************************************************
    // * Paramater * Swap mode      * data bits translation                     *
    // **************************************************************************
    // *           *                * D_Type(31:24) * D_Type(23:16) * D_Type(15:8)  *  D_Type(7:0)  *
    // **************************************************************************
    // * Long_mode * no swap 32-bit * Q_Type(31:24) * Q_Type(23:16) * Q_Type(15:8)  *  Q_Type(7:0)  *
    // * Word_mode * 16 bit         * Q_Type(15:8)  * Q_Type(7:0)   * Q_Type(31:24) * Q_Type(23:16) *
    // * Byte_mode * 8 bit          * Q_Type(7:0)   * Q_Type(15:8)  * Q_Type(23:16) * Q_Type(31:24) *
    // **************************************************************************

typedef DLL_DEF BYTE CALL_CONV GetScrTransactionType_Type( void );
    // this function return a byte representing the current swaping mode.

typedef DLL_DEF USHORT CALL_CONV scr_csr_read_Type( char csr_number );
    // Returns contents of CSR register specifed as a parameter.

typedef DLL_DEF void CALL_CONV scr_csr_write_Type( char csr_number, USHORT regval );
    // Write given value to the CSR register specifed as a parameter.

typedef DLL_DEF DWORD CALL_CONV ReadSCRLong_Type( DWORD offset, DWORDPTR lnValue);
    // Returns long word value read from scramnet card at the given offset.
    // offset specifed as number of long words from base address to desired value.

typedef DLL_DEF DWORD CALL_CONV WriteSCRLong_Type( DWORD offset, DWORD lnValue);
    // returns long word writen to SCRAMNet card at the given offset.
    // offset specifed as number of long words from base address to desired value.

typedef DLL_DEF WORD CALL_CONV ReadSCRWord_Type( DWORD offset, WORDPTR nValue);
    // returns word value read from scramnet card at the given offset.
    // offset specifed as number of words from base address to desired value.

typedef DLL_DEF WORD CALL_CONV WriteSCRWord_Type( DWORD offset, WORD nValue);
    // returns word writen to SCRAMNet card at the given offset.
    // offset specifed as number of words from base address to desired value.
    
typedef DLL_DEF BYTE CALL_CONV ReadSCRByte_Type( DWORD offset, BYTEPTR nValue);
    // returns byte value read from scramnet card at the given offset. 
    // offset specifed as number of bytes from base address to desired value.
    
typedef DLL_DEF BYTE CALL_CONV WriteSCRByte_Type( DWORD offset, BYTE lnValue);
    // returns byte writen to SCRAMNet card at the given offset. 
    // offset specifed as number of bytes from base address to desired value.
    
typedef DLL_DEF DWORD CALL_CONV get_scr_phy_csr_addr_Type( void ); 
    // Returns physical memory address of the SCRAMNet CSR base resgister.
    
typedef DLL_DEF DWORD CALL_CONV get_scr_phy_mem_addr_Type( void );
    // Returns physical memory address of SCRAMNet memory base address.
    
typedef DLL_DEF BYTE CALL_CONV get_scr_node_id_Type(  void );
    // Returns a byte value in range 0 to 255 for SCRAMNet node id.
    
typedef DLL_DEF BYTE CALL_CONV get_scr_time_out_Type( void );
    // Returns a byte value in range 0 to 255 for SCRAMNet Timeout value
    
typedef DLL_DEF DWORD CALL_CONV get_scr_user_mem_size_Type( void );
    // Return an unsigned long value equal to the memory size in bytes 
    // specifed in the SCRAMNET.INI file.
    // Note: ini file specifies memory size in Kbytes. Function returns bytes.
    
typedef DLL_DEF DWORD CALL_CONV sp_mem_size_Type( void );
    // Return an unsigned long values equal to the number of bytes of 
    // of SCRAMNet memmory as represented in csr 8.
                         
typedef DLL_DEF void CALL_CONV scr_board_status_Type( HWND hwndParent);
    // displays a message window with SCRAMNet configuration information in it.
    
typedef DLL_DEF void CALL_CONV scr_mclr_mm_Type( SCR_INT arg );
    // Clear all of memory or ACR bits depending on parameter passed in arg.
    // To clear memory use defined value 'MEM' as the parameter or 
    // to clear ACR  use defined value 'ACR'.
    
typedef DLL_DEF ULONG CALL_CONV scr_probe_mm_Type( void* addr_ptr, unsigned short md_flg );
    // Determines validity of specified address.

typedef DLL_DEF DWORD CALL_CONV sw_mem_addr_Type( void );
    // Returns physical memory address of SCRAMNet memory base address.
    
typedef DLL_DEF DWORD CALL_CONV sw_reg_addr_Type( void );
    // Returns physical memory address of SCRAMNet memory base address.
    
typedef DLL_DEF DWORD CALL_CONV sw_user_size_Type( void );
    // Return an unsigned long value equal to the memory size in bytes 
    // specifed in the Registry.
    // Note: Registry specifies memory size in Kbytes. Function returns bytes.
    
typedef DLL_DEF SCR_INT CALL_CONV sw_cfg_fill_Type( void *ConfigStruct );
    // Fills DOS/unix configuration structure
    
typedef DLL_DEF VOID CALL_CONV scr_id_mm_Type( char *nID, char *nCnt );
    // Fills byte value in range 0 to 255 for SCRAMNet node id and total nodes on net
    
typedef DLL_DEF SCR_INT CALL_CONV sw_net_to_Type( void );
    // Returns a byte value in range 0 to 255 for SCRAMNet Timeout value
    
typedef DLL_DEF BOOL CALL_CONV sw_set_size_Type( DWORD lnNewSize ); 
    // Write new "user-specified" memory size to Registry _Type(this amount will be mapped
    // versus the amount on the card).
    
typedef DLL_DEF BYTE CALL_CONV sw_get_int_Type( void ); 
    // Read interrupt number from Registry.

typedef DLL_DEF BOOL CALL_CONV sw_set_int_Type( BYTE nIntNum );
    // Write new interrupt number to Registry.
    
typedef DLL_DEF SCR_INT CALL_CONV scr_mem_mm_Type( SCR_INT arg );
    // Maps/unmaps SCRAMNet memory
    
typedef DLL_DEF SCR_INT CALL_CONV scr_reg_mm_Type( SCR_INT arg );
    // Maps/unmaps SCRAMNet memory
    
typedef DLL_DEF SCR_INT CALL_CONV scr_brd_select_Type( SCR_INT brd );
    // Changes control of SCRAMNet boards
    
    // DMA read from SCRAMNet memory to user buffer
typedef DLL_DEF SCR_INT CALL_CONV scr_dma_read_Type( PVOID user_addr, ULONG scr_offset, ULONG num_bytes );
    
    // DMA write from user buffer to SCRAMNet memory
typedef DLL_DEF SCR_INT CALL_CONV scr_dma_write_Type( PVOID user_addr, ULONG scr_offset, ULONG num_bytes );
    
typedef DLL_DEF SCR_INT CALL_CONV sp_cfg_read_Type( SCR_INT board_number );
    // Function unnecessary in Windows NT _Type(here for compatibility).
    
typedef DLL_DEF unsigned  char CALL_CONV scr_acr_read_Type( unsigned long mem_loc );
    // Reads specified ACR register
    
typedef DLL_DEF void CALL_CONV scr_acr_write_Type( unsigned long mem_loc, unsigned char acr_val );
    // Writes to a specified ACR register
    
typedef DLL_DEF void CALL_CONV scr_error_mm_Type( FILE * ofd, unsigned short int tmp_csr );
    // Provides textual description of errors
    
typedef DLL_DEF SCR_INT CALL_CONV scr_fswin_mm_Type( void );
    // Checks the state of the "Fiber Optic Bypass Not Connected" bit in CSR1
    
typedef DLL_DEF void CALL_CONV scr_fifo_mm_Type( SCR_INT cmd, struct rd_fifo* f_ptr );
    // Reset shared memory, interrupt, and Tx/Tx FIFO or read CSR1
    
typedef DLL_DEF SCR_INT CALL_CONV scr_load_mm_Type( char *str_ptr, SCR_INT cmd );
    // Loads user-supplied configuration file
    
typedef DLL_DEF SCR_INT CALL_CONV scr_read_int_fifo_Type( unsigned long int *fifo_value );
    // Reads interrupt FIFO.
    
typedef DLL_DEF void CALL_CONV scr_rw_mm_Type( struct rw_scr *op ); 
    // Reads/writes specified CSR.
    
typedef DLL_DEF SCR_INT CALL_CONV scr_save_mm_Type( char *strptr, SCR_INT cmd ); 
    // Saves memory or ACR contents to file.
    
typedef DLL_DEF void CALL_CONV scr_smem_mm_Type( SCR_INT arg, unsigned long value );
    // Set memory or ACR to value.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_bist_rd_Type( SCR_INT *bitstream );
    // Reads built-in-self-test info from Plus/LX cards.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_msg_life_Type( SCR_INT hops );
    // Set pre-age of network messages.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_net_to_Type( unsigned short timeout );
    // Set network timeout.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_protocol_Type( SCR_INT ProtocolMode );
    // Set network protocol.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_rx_id_Type( unsigned char NewID ); 
    // Set node receive ID.

typedef DLL_DEF SCR_INT CALL_CONV sp_set_cntr_Type( SCR_INT mode );
    // Set general purpose counter.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_set_sm_addr_Type( unsigned long addr );
    // Set physical memory address.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_set_vp_Type( SCR_INT request, SCR_INT pagenumber );
    // Set virtual page number.
    
typedef DLL_DEF SCR_INT CALL_CONV sp_txrx_id_Type( unsigned char NewID ); 
    // Set transmit/receive ID.
    
typedef DLL_DEF void CALL_CONV scr_reset_mm_Type( void );
    // Initializes node to zero condition. 
    
typedef DLL_DEF SCR_INT CALL_CONV sp_plus_find_Type( void );
    // Determines card type. 
    
typedef DLL_DEF BOOL CALL_CONV sp_stm_mm_Type( BYTE mode );
    // Sets transaction type.
    
typedef DLL_DEF BYTE CALL_CONV sp_gtm_mm_Type( void );
    // Gets transaction type.
    
typedef DLL_DEF void CALL_CONV scr_bswp_mm_Type( void );
    // Sets byteswap mode _Type(invalid for PCI).
    
typedef DLL_DEF void CALL_CONV scr_dfltr_mm_Type( SCR_INT arg );
    // Data filtering control switch.
    
typedef DLL_DEF void CALL_CONV scr_lnk_mm_Type( SCR_INT cmd );
    // Link SCRAMNet node to network.
    
typedef DLL_DEF void CALL_CONV scr_wml_mm_Type( SCR_INT arg );
    // Set update mode.
    
typedef DLL_DEF void CALL_CONV scr_acr_mm_Type( SCR_INT enab_fl );
    // Enable ACRs.
    
typedef DLL_DEF void CALL_CONV scr_int_mm_Type( SCR_INT cmd, SCR_INT arg );
    // Set interrupt mode.
    
typedef DLL_DEF BOOL CALL_CONV sw_int_connect_Type( void );
    // Connect interrupt processing.

typedef DLL_DEF BOOL CALL_CONV sw_int_disconnect_Type( void );
    // Disconnect interrupt processing.

typedef DLL_DEF BOOL CALL_CONV sw_int_snapicon_Type( void );
    // Connect interrupt processing.

typedef DLL_DEF BOOL CALL_CONV sw_int_snapidis_Type( void );
    // Disconnect interrupt processing.

typedef DLL_DEF SCR_INT CALL_CONV scr_delay_Type(UINT delay);
    // Provides a general delay in ms

class TScramnetDll {
private:

   HINSTANCE                 Dll;

public:

   TScramnetDll();
   virtual ~TScramnetDll();


   get_base_mem_Type                     * get_base_mem;
   get_scr_node_id_Type                  * get_scr_node_id;
   get_scr_phy_csr_addr_Type             * get_scr_phy_csr_addr;
   get_scr_phy_mem_addr_Type             * get_scr_phy_mem_addr;
   get_scr_time_out_Type                 * get_scr_time_out;
   get_scr_user_mem_size_Type            * get_scr_user_mem_size;
   scr_acr_mm_Type                       * scr_acr_mm;
   scr_acr_read_Type                     * scr_acr_read;
   scr_acr_write_Type                    * scr_acr_write;
   scr_board_status_Type                 * scr_board_status;
   scr_brd_select_Type                   * scr_brd_select;
   scr_bswp_mm_Type                      * scr_bswp_mm;
   scr_byte_mem_exist_Type               * scr_byte_mem_exist;
   scr_csr_write_Type                    * scr_csr_write;
   scr_delay_Type                        * scr_delay;
   scr_dfltr_mm_Type                     * scr_dfltr_mm;
   scr_dma_read_Type                     * scr_dma_read;
   scr_dma_write_Type                    * scr_dma_write;
   scr_error_mm_Type                     * scr_error_mm;
   scr_fifo_mm_Type                      * scr_fifo_mm;
   scr_fswin_mm_Type                     * scr_fswin_mm;
   scr_id_mm_Type                        * scr_id_mm;
   scr_int_mm_Type                       * scr_int_mm;
   scr_lnk_mm_Type                       * scr_lnk_mm;
   scr_load_mm_Type                      * scr_load_mm;
   scr_long_mem_exist_Type               * scr_long_mem_exist;
   scr_mclr_mm_Type                      * scr_mclr_mm;
   scr_mem_mm_Type                       * scr_mem_mm;
   scr_probe_mm_Type                     * scr_probe_mm;
   scr_read_int_fifo_Type                * scr_read_int_fifo;
   scr_reg_mm_Type                       * scr_reg_mm;
   scr_reset_mm_Type                     * scr_reset_mm;
   scr_rw_mm_Type                        * scr_rw_mm;
   scr_save_mm_Type                      * scr_save_mm;
   scr_short_mem_exist_Type              * scr_short_mem_exist;
   scr_smem_mm_Type                      * scr_smem_mm;
   scr_wml_mm_Type                       * scr_wml_mm;
   sp_bist_rd_Type                       * sp_bist_rd;
   sp_cfg_read_Type                      * sp_cfg_read;
   sp_gtm_mm_Type                        * sp_gtm_mm;
   sp_mem_size_Type                      * sp_mem_size;
   sp_msg_life_Type                      * sp_msg_life;
   sp_net_to_Type                        * sp_net_to;
   sp_plus_find_Type                     * sp_plus_find;
   sp_protocol_Type                      * sp_protocol;
   sp_rx_id_Type                         * sp_rx_id;
   sp_scram_init_Type                    * sp_scram_init;
   sp_set_cntr_Type                      * sp_set_cntr;
   sp_set_sm_addr_Type                   * sp_set_sm_addr;
   sp_set_vp_Type                        * sp_set_vp;
   sp_stm_mm_Type                        * sp_stm_mm;
   sp_txrx_id_Type                       * sp_txrx_id;
   sw_cfg_fill_Type                      * sw_cfg_fill;
   sw_get_int_Type                       * sw_get_int;
   sw_int_connect_Type                   * sw_int_connect;
   sw_int_disconnect_Type                * sw_int_disconnect;
   sw_int_snapicon_Type                  * sw_int_snapicon;
   sw_int_snapidis_Type                  * sw_int_snapidis;
   sw_mem_addr_Type                      * sw_mem_addr;
   sw_net_to_Type                        * sw_net_to;
   sw_reg_addr_Type                      * sw_reg_addr;
   sw_set_int_Type                       * sw_set_int;
   sw_set_size_Type                      * sw_set_size;
   sw_user_size_Type                     * sw_user_size;

};


#endif
