#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <iostream>


namespace MatrSpace {

//--------------------------------------------------------------------------------//
template< class T >
  class AbstractMatr {
protected :
   std::vector< std::vector< T > > Matrix ;
public :
  AbstractMatr() {}
  AbstractMatr( size_t n, size_t m ) ;
  AbstractMatr( const AbstractMatr &Ob ) : Matrix( Ob.Matrix ) {}
  virtual ~AbstractMatr() {}
  void SetSize( size_t n, size_t m ) ;
  inline const size_t GetRow() const { return Matrix.size()    ; }
  inline const size_t GetCol() const { return Matrix[0].size() ; }
  void swap( AbstractMatr & ) ;

};
//--------------------------------------------------------------------------------//
template< class T >
  class MathMatr : public AbstractMatr< T > {
public :
  MathMatr() : AbstractMatr() {}
  MathMatr( size_t n, size_t m ) : AbstractMatr< T >( n, m ) {}
  MathMatr( const AbstractMatr< T > &Ob ) : AbstractMatr< T >( Ob ) {}
  virtual ~MathMatr() {}
  const MathMatr< T >& operator  =( const MathMatr& )       ;
  const MathMatr< T >& operator +=( const MathMatr& )       ;
  const MathMatr< T >  operator  +( const MathMatr& ) const ;
  const MathMatr< T >& operator *=( const MathMatr& )       ;
  const MathMatr< T >  operator  *( const MathMatr& ) const ;
  virtual void input ( std::istream& )       {}
  virtual void output( std::ostream& ) const {}
  template< class T2 >
    friend std::ostream& operator <<( std::ostream&, const MathMatr< T2 > &Ob ) ;
  template< class T2 >
    friend std::istream& operator >>( std::istream&, MathMatr< T2 > &Ob ) ;
  void random_fill() ;
};
//--------------------------------------------------------------------------------//
template< class T >
  class IOMatr : public MathMatr< T > {
public :
  IOMatr() : MathMatr< T >() {}
  IOMatr( size_t n, size_t m ) : MathMatr( n, m ) {}
  IOMatr( const AbstractMatr< T > &Ob ) : MathMatr( Ob ) {}
  virtual ~IOMatr() {}
  virtual void input ( std::istream& )       = 0 ;
  virtual void output( std::ostream& ) const = 0 ;
};
//--------------------------------------------------------------------------------//
template< class T >
  class ConsoleMatr : public IOMatr< T > {
public :
  ConsoleMatr() : IOMatr< T >() {}
  ConsoleMatr( size_t n, size_t m ) : IOMatr( n, m ) {}
  ConsoleMatr( const AbstractMatr< T > &Ob ) : IOMatr( Ob ) {}
  virtual ~ConsoleMatr() {}
  const ConsoleMatr< T >& operator  =( const ConsoleMatr& )       ;
  const ConsoleMatr< T >& operator +=( const ConsoleMatr& )       ;
  const ConsoleMatr< T >  operator  +( const ConsoleMatr& ) const ;
  const ConsoleMatr< T >& operator *=( const ConsoleMatr& )       ;
  const ConsoleMatr< T >  operator  *( const ConsoleMatr& ) const ;
  virtual void input ( std::istream& )      ;
  virtual void output( std::ostream& ) const;
};
//--------------------------------------------------------------------------------//
  
//*****************************************************************************//
template< class T >
  AbstractMatr< T >::AbstractMatr( size_t n, size_t m ) {
    Matrix.resize( n ) ;
    for( size_t i = 0 ; i != GetRow() ; ++i ) Matrix[i].resize( m ) ;
}
//*****************************************************************************//
template< class T >
  void AbstractMatr< T >::SetSize( size_t n, size_t m ) {
    if( GetRow() != 0 && GetCol() != 0 ) Matrix.clear() ;
    Matrix.resize(n) ;
    for ( size_t i = 0 ; i != GetRow() ; ++i ) Matrix[i].resize( m ) ;
}
//*****************************************************************************//
template< class T >
  void AbstractMatr< T >::swap( AbstractMatr< T > &Ob ) {
    Matrix.swap( Ob.Matrix ) ;
}
//*****************************************************************************//
template< class T >
  const MathMatr< T >& MathMatr< T >::operator =( const MathMatr< T > &Ob ) {
    MathMatr< T > Temp( Ob ) ;
    Temp.swap( *this ) ;

return *this ;
}
//*****************************************************************************//
template< class T >
  const MathMatr< T >& MathMatr< T >::operator +=( const MathMatr< T > &Ob ) {
    if( GetRow() != Ob.GetRow() && GetCol() != Ob.GetCol() )
      throw std::invalid_argument( "Size of two matrix for sum must be equal!" ) ;
    
    for( size_t i = 0 ; i != Ob.GetRow() ; ++i )
      for( size_t j = 0 ; j != Ob.GetCol() ; ++j )
        Matrix[i][j] += Ob.Matrix[i][j] ;

return *this ;
}
//*****************************************************************************//
template< class T >
  const MathMatr< T > MathMatr<T>::operator +( const MathMatr< T > &Ob ) const {
    MathMatr< T > Temp( *this );
    Temp += Ob;

return Temp;
}
//*****************************************************************************//
template< class T >
  const MathMatr< T >& MathMatr< T >::operator *=( const MathMatr< T > &Ob ) {
    if( GetCol() != Ob.GetRow() )
        throw std::invalid_argument( "Num of 1-st matrix cols 
                                     must be equal to num of 2-nd matrix rows" ) ;

    MathMatr Temp( GetRow(), Ob.GetCol() ) ;
    for( size_t i = 0 ; i != Temp.GetRow() ; ++i ) {
      for( size_t j = 0 ; j != Temp.GetCol() ; ++j ) {
        Temp.Matrix[i][j] = 0 ;
        for( size_t k = 0 ; k != GetCol() ; ++k )
          Temp.Matrix[i][j] += Matrix[i][k] * Ob.Matrix[k][j] ;
      }
    }
    *this = Temp ;

return *this ;
}
//*****************************************************************************//
template< class T >
  const MathMatr< T > MathMatr< T >::operator *( const MathMatr< T > &Ob ) const {
    MathMatr< T > Temp( *this ) ;
    Temp *= Ob ;

return Temp ;
}
//*****************************************************************************//
template< class T >
  void MathMatr< T >::random_fill() {
    for(size_t i = 0 ; i != GetRow() ; ++i )
      for( size_t j = 0 ; j != GetCol() ; ++j )
        Matrix[i][j] = 1 + rand() % 50 ;
}
//*****************************************************************************//
template< class T >
  std::ostream& operator <<( std::ostream &os, const MathMatr< T > &Ob ) {
    Ob.output( os ) ;

return os ;
}
//*****************************************************************************//
template< class T >
  std::istream& operator >>( std::istream &is, MathMatr< T > &Ob ) {
    Ob.input( is ) ;

return is ;
}
//*****************************************************************************//
template< class T >
  void ConsoleMatr<T>::input(std::istream& is) {
    for( size_t i = 0 ; i != GetRow() ; ++i )
      for( size_t j = 0 ; j != GetCol() ; ++j ) {
        std::cout << "Enter Matrix [" << i + 1 << "][" << j + 1 << "]: " ;
        is >> Matrix[i][j] ;
      }
}
//*****************************************************************************//
template< class T >
  void ConsoleMatr< T >::output( std::ostream &os ) const {
    for( size_t i = 0 ; i != GetRow() ; ++i ) {
      for( size_t j = 0 ; j != GetCol() ; ++j ) 
        os << std::setw( 5 ) << Matrix[i][j] << ' ' ;
      std::cout << "\n" ;
    }
}
//*****************************************************************************//
template< class T >
  const ConsoleMatr< T >& ConsoleMatr< T >::operator =( const ConsoleMatr< T > &Ob ) {
    ConsoleMatr Temp( Ob ) ;
    Temp.swap( *this ) ;

return *this ;
}
//*****************************************************************************//
template< class T >
  const ConsoleMatr< T >& ConsoleMatr< T >::operator +=( const ConsoleMatr< T > &Ob) {
    if( GetRow() != Ob.GetRow() && GetCol() != Ob.GetCol() )
      throw std::invalid_argument("Size of two matrix for sum must be equal!");
    
    for( size_t i = 0 ; i != Ob.GetRow() ; ++i )
      for( size_t j = 0 ; j != Ob.GetCol() ; ++j )
        Matrix[i][j] += Ob.Matrix[i][j] ;

return *this;
}
//*****************************************************************************//
template< class T >
  const ConsoleMatr< T > ConsoleMatr< T >::operator +( const ConsoleMatr< T > &Ob) const {
    ConsoleMatr< T > Temp( *this ) ;
    Temp += Ob ;
return Temp ;
}
//*****************************************************************************//
template< class T >
  const ConsoleMatr< T >& ConsoleMatr< T >::operator *=( const ConsoleMatr< T > &Ob) {
    if ( GetCol() != Ob.GetRow() )
      throw std::invalid_argument( "Num of 1-st matrix cols must be 
                                   equal to num of 2-nd matrix rows" ) ;
    
    ConsoleMatr Temp( GetRow(), Ob.GetCol() ) ;
    for( size_t i = 0 ; i != Temp.GetRow() ; ++i )
      for( size_t j = 0 ; j != Temp.GetCol() ; ++j )
        for( size_t k = 0 ; k != GetCol() ; ++k )
          Temp.Matrix[i][j] += Matrix[i][k] * Ob.Matrix[k][j] ;  
    *this = Temp ;

return *this ;
}
//*****************************************************************************//
template< class T >
  const ConsoleMatr< T > ConsoleMatr< T >::operator *( const ConsoleMatr< T > &Ob) const {
    ConsoleMatr< T > Temp( *this ) ;
    Temp *= Ob ;
return Temp ;
}
//*****************************************************************************//

} //namespace MatrSpace
#endif