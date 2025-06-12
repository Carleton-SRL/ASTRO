#ifndef INTERFACEOPTIONS_H
#define INTERFACEOPTIONS_H

class TIntOptions {
public:
   bool ValidInterface;
public:
   TIntOptions() {}
   virtual ~TIntOptions() {}
};

class TGpibOptions : public TIntOptions {
public:
   int BoardIndex;
   int PrimaryAddr;
public:
   TGpibOptions(): BoardIndex( 0 ), PrimaryAddr( 0 ) {}
   TGpibOptions( const int InBoardIndex, const int InPrimaryAddr ) :
      BoardIndex( InBoardIndex ), PrimaryAddr( InPrimaryAddr ) {}

};

#endif
 