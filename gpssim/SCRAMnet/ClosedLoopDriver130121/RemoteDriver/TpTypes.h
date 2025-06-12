#ifndef TpTypesH
#define TpTypesH

//---------------------------------------------------------------------------
//
// $Workfile:: TpTypes.h                                             $
//
// $Revision:: 3                                                     $
//
// $History:: TpTypes.h                                              $
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/28/02    Time: 3:28p
//Updated in $/TapMsec
//Change header guard to standard
//Added Source Safe keywords
//Used std:: instead of global using names std
//Added TDcm and TVector
//Added include guards
//
//
//---------------------------------------------------------------------------



typedef std::vector<int>           TIntArr;
typedef std::vector<double>        TDoubleArr;
typedef std::vector<bool>          TBoolArr;
typedef std::vector<unsigned char> TUCharArr;
typedef std::vector<char>          TCharArr;

typedef std::set<int>              TIntSet;

typedef techsoft::matrix<double>   TMatrix;

typedef std::valarray<double>      TValArray;

#endif
