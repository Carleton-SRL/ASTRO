#ifndef BStreamH
#define BStreamH

//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
//---------------------------------------------------------------------------


#pragma pack(push,1)

// Binary output file stream

class bofstream: private std::ofstream {
public:
   bofstream
      (
      const AnsiString &FileName
      ) :
      std::ofstream( FileName.c_str(), std::ios::out | std::ios::binary)
   {
   }

   bofstream
      (
      const char *fn
      ) :
      std::ofstream(fn, std::ios::out | std::ios::binary)
   {
   }
   bofstream() : std::ofstream() { }

   void Write
      (
      const void * const p,
      const int          len
      )
   {
      if ( !p )       return;
      if ( len <= 0 ) return;
      write( (char *) p, len );
   }

   void open
      (
      const AnsiString &FileName
      )
   {
      std::ofstream::open( FileName.c_str(), std::ios::out | std::ios::binary );
   }
   void open
      (
      const char *fn
      )
   {
      std::ofstream::open( fn, std::ios::out | std::ios::binary );
   }
   // MDW - Problem with template specialization.  Compiler complains that bodies are already
   // defined.  Having general template for writing by taking pointer and sizeof is probably not
   // a good idea anyway, so just define the built-in types.  Unfortunately, I don't know of a way
   // to define the template, and instantiate it only for the built-in types.  Probably Loki will
   // do it.
#if(0)
   template <typename T>
   friend bofstream & operator<<
      (
      bofstream &bfs,
      T &t
      )
   {
      bfs.write( (char *) &t, sizeof( t ) );
      return bfs;
   }
#else
   friend bofstream & operator<< ( bofstream & bfs,  int &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
   friend bofstream & operator<< ( bofstream & bfs,  unsigned int &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  short &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
   friend bofstream & operator<< ( bofstream & bfs,  unsigned short &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  long &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
   friend bofstream & operator<< ( bofstream & bfs,  unsigned long &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  char &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
   friend bofstream & operator<< ( bofstream & bfs,  unsigned char &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  __int64 &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
   friend bofstream & operator<< ( bofstream & bfs,  unsigned __int64 &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  double &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  long double &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  float &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }

   friend bofstream & operator<< ( bofstream & bfs,  bool &x ) { bfs.Write( &x, sizeof(x) ); return( bfs ); }
#endif
//  inline operator void*() const
//  {
//    return fail() ? (void*)0 : (void*)1;
//  }
    using std::ofstream::operator void *;
    using std::ofstream::seekp;
    using std::ofstream::tellp;
    using std::ofstream::write;
    using std::ofstream::close;
    using std::ofstream::operator!;
    using std::ofstream::clear;
    using std::ofstream::eof;
    using std::ofstream::flush;
    using std::ofstream::good;
//    using std::ofstream::seekg;
//    using std::ofstream::tellg;
};

//-----------------------------------------------------------------------------
// Binary input file stream
//
class bifstream: private std::ifstream {
public:

   bifstream
      (
      const AnsiString & FileName
      ) : std::ifstream( FileName.c_str(), std::ios::in | std::ios::binary )
   { }
   bifstream
      (
      const char *fn
      ) : std::ifstream(fn, std::ios::in | std::ios::binary)
   { }

   bifstream() : std::ifstream() { }
   void open
      (
      const AnsiString & FileName
      )
   {
      std::ifstream::open( FileName.c_str(), std::ios::in | std::ios::binary);
   }
   void open
      (
      const char *fn
      )
   {
      std::ifstream::open(fn, std::ios::in | std::ios::binary);
   }

   void Read
      (
      void        * p,
      const int     len
      )
   {
      if ( !p )       return;
      if ( len <= 0 ) return;

      read( (char *) p, len );

   }

   // MDW - Problem with template specialization.  Compiler complains that bodies are already
   // defined.  Having general template for writing by taking pointer and sizeof is probably not
   // a good idea anyway, so just define the built-in types.  Unfortunately, I don't know of a way
   // to define the template, and instantiate it only for the built-in types.  Probably Loki will
   // do it.
#if(0)
   template <class T>
   friend bifstream & operator>>
      (
      bifstream &bifs,
      T &t
      )
   {
      bifs.readBytes( &t, sizeof( t ) );
      return bifs;
   }
#else

   friend bifstream & operator>> ( bifstream & bfs,  int &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }
   friend bifstream & operator>> ( bifstream & bfs,  unsigned int &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  short &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }
   friend bifstream & operator>> ( bifstream & bfs,  unsigned short &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  long &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }
   friend bifstream & operator>> ( bifstream & bfs,  unsigned long &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  char &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }
   friend bifstream & operator>> ( bifstream & bfs,  unsigned char &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  __int64 &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }
   friend bifstream & operator>> ( bifstream & bfs,  unsigned __int64 &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  double &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  long double &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  float &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

   friend bifstream & operator>> ( bifstream & bfs,  bool &x ) { bfs.Read( &x, sizeof(x) ); return( bfs ); }

#endif

  /*
   * operator bool() const
   */

  inline operator void*() const
  {
    return fail() ? (void*)0 : (void*)1;
  }
//    using std::ifstream::basic_ios::operator void*;
    using std::ifstream::operator!;
    using std::ifstream::clear;
    using std::ifstream::read;
    using std::ifstream::close;
    using std::ifstream::good;
    using std::ifstream::seekg;
    using std::ifstream::tellg;
    using std::ifstream::eof;
    using std::ifstream::fail;

};

#if(0)
class bfstream: private fstream {
public:
   bfstream
      (
      const AnsiString & FileName,
      int state = ( std::ios::in | std::ios::out | std::ios::binary )
      ) :
      fstream( FileName.c_str(), ( state | std::ios::in | std::ios::out | std::ios::binary ) )
   { }

   bfstream
      (
      const char *fn,
      int state = ( std::ios::in | std::ios::out | std::ios::binary )
      ) :
      fstream(fn, ( state | std::ios::in | std::ios::out | std::ios::binary ) )
   { }

   bfstream() : fstream() {}

   void writeBytes
      (
      const void *p,
      int len
      )
   {
     if ( !p )       return;
     if ( len <= 0 ) return;
     write( (char *) p, len );
   }

   void readBytes
      (
      void *p,
      int len
      )
   {
      if (!p)       return;
      if (len <= 0) return;
      read( (char *) p, len );
   }

   void open
      (
      const AnsiString & FileName,
      int state = ( std::ios::in | std::ios::out | std::ios::binary )
      )
    {
       fstream::open( FileName.c_str(), ( state | std::ios::in | std::ios::out | std::ios::binary ) );
    }

   void open
      (
      const char *fn,
      int state = ( std::ios::in | std::ios::out | std::ios::binary )
      )
    {
       fstream::open( fn, ( state | std::ios::in | std::ios::out | std::ios::binary ) );
    }

   template <class T>
   friend bfstream & operator>>
      (
      bfstream &bfs,
      T &t
      )
   {
      bfs.readBytes( &t, sizeof( t ) );
      return bfs;
   }
   template <class T>
   friend bfstream & operator<<
      (
      bfstream &bfs,
      const T &t
      )
   {
      bfs.writeBytes( &t, sizeof( t ) );
      return bfs;
   }

    using std::fstream::good;
    using std::fstream::fail;
    using std::fstream::eof;
    using std::fstream::seekp;
    using std::fstream::tellp;
    using std::fstream::read;
    using std::fstream::write;
    using std::fstream::close;
    using std::fstream::clear;
    using std::fstream::seekg;
    using std::fstream::tellg;
    using std::fstream::operator!;


};

#endif

#pragma pack(pop)


#endif



