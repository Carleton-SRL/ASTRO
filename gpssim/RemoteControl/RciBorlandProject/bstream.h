/* ----------------------------------------------------------- *\
**  bstream.h -- Header for bofstream and bifstream classes    **
** ----------------------------------------------------------- **
**                                                             **
** ----------------------------------------------------------- **
**     Copyright (c) 1993 by Tom Swan. All rights reserved     **
\* ----------------------------------------------------------- */

#ifndef __BSTREAM_H
#define __BSTREAM_H     // Prevent multiple #includes

#include <iostream.h>
#include <fstream.h>

using namespace std;

#pragma pack(push,1)

// Binary output file stream

class bofstream: private ofstream {
public:
  bofstream(const char *fn)
    : ofstream(fn, ios::out | ios::binary) { }
  bofstream() : ofstream() { }
  void writeBytes(const void *p, int len)
  {
     if ( !p ) return;
     if ( len <= 0 ) return;
     write((char *)p,len);
  }

  void open (const char *fn) {
	  ofstream::open(fn, ios::out | ios::binary); }
   template <class T>
   friend bofstream & operator<< (bofstream &bfs, T &t)
   {
      bfs.writeBytes(&t, sizeof(t));
      return bfs;
   }
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

// Binary input file stream

class bifstream: private ifstream {
public:

   bifstream
      (
      const char *fn
      ) : ifstream(fn, ios::in | ios::binary)
   { }

   bifstream() : ifstream() { }
   void open
      (
      const char *fn
      )
   {
	   ifstream::open(fn, ios::in | ios::binary);
   }

   void readBytes
      (
      void *p,
      const int len
      )
   {
      if (!p)       return;
      if (len <= 0) return;

      read((char *)p, len);

   }

   template <class T>
   friend bifstream & operator>> (bifstream &bifs, T &t)
   {
      bifs.readBytes(&t, sizeof(t));
      return bifs;
   }

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

class bfstream: private fstream {
public:
   bfstream(const char *fn,int state=ios::in | ios::out | ios::binary)
    : fstream(fn, state|ios::in | ios::out | ios::binary) { }
   bfstream() : fstream() {}
   void writeBytes(const void *p, int len)
   {
     if ( !p ) return;
     if ( len <= 0 ) return;
     write((char *)p,len);
   }
   void readBytes(void *p, int len)
   {
      if (!p) return;
      if (len <= 0) return;
      read((char *)p, len);
   }
   void open(const char *fn, int state=ios::in | ios::out | ios::binary)
    { fstream::open(fn, state|ios::in | ios::out | ios::binary); }
   template <class T>
   friend bfstream & operator>> (bfstream &bfs, T &t)
   {
      bfs.readBytes(&t, sizeof(t));
      return bfs;
   }
   template <class T>
   friend bfstream & operator<< (bfstream &bfs, const T &t)
   {
      bfs.writeBytes(&t, sizeof(t));
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

#pragma pack(pop)


#endif  // __BSTREAM_H


//---------------------------------------------------------------
// Copyright (c) 1993 by Tom Swan. All rights reserved.
// Revision 1.00    Date: 02/12/1993   Time: 07:51 am
