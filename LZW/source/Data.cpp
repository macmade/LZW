/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2020 Jean-David Gadina - www.xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        Data.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <LZW/Data.hpp>
#include <cstring>
#include <iomanip>

namespace LZW
{
    Data::Data():
        Data( std::vector< uint8_t > {} )
    {}
    
    Data::Data( uint8_t value ):
        Data()
    {
        *( this ) += value;
    }
    
    Data::Data( uint16_t value ):
        Data()
    {
        *( this ) += value;
    }
    
    Data::Data( uint32_t value ):
        Data()
    {
        *( this ) += value;
    }
    
    Data::Data( uint64_t value ):
        Data()
    {
        *( this ) += value;
    }
    
    Data::Data( const std::string & value ):
        Data()
    {
        this->_append( reinterpret_cast< const uint8_t * >( &( value[ 0 ] ) ), value.size() );
    }
    
    Data::Data( const std::vector< uint8_t > & value ):
        _bytes( value )
    {}
    
    Data::Data( const Data & o ):
        _bytes( o._bytes )
    {}
    
    Data::Data( Data && o ):
        _bytes( std::move( o._bytes ) )
    {}
    
    Data::~Data()
    {}
    
    Data & Data::operator =( Data o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    bool Data::operator ==( const Data & o ) const
    {
        return this->_bytes == o._bytes;
    }
    
    bool Data::operator !=( const Data & o ) const
    {
        return this->_bytes != o._bytes;
    }
    
    bool Data::operator >( const Data & o ) const
    {
        return this->_bytes > o._bytes;
    }
    
    bool Data::operator <( const Data & o ) const
    {
        return this->_bytes < o._bytes;
    }
    
    bool Data::operator >=( const Data & o ) const
    {
        return this->_bytes >= o._bytes;
    }
    
    bool Data::operator <=( const Data & o ) const
    {
        return this->_bytes <= o._bytes;
    }
    
    Data & Data::operator +=( uint8_t value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( uint16_t value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( uint32_t value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( uint64_t value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( const Data & value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( const std::string & value )
    {
        this->append( value );
        
        return *( this );
    }
    
    Data & Data::operator +=( const std::vector< uint8_t > & value )
    {
        this->append( value );
        
        return *( this );
    }
    
    uint8_t Data::operator []( std::size_t index ) const
    {
        if( this->_bytes.size() <= index )
        {
            throw std::out_of_range( "Index is out of bounds: " + std::to_string( index ) );
        }
        
        return this->_bytes[ index ];
    }
    
    Data::operator std::vector< uint8_t >() const
    {
        return this->bytes();
    }
    
    Data::operator std::string() const
    {
        return this->string();
    }
    
    std::size_t Data::hash() const
    {
        std::size_t h = this->_bytes.size();
        
        for( const auto & b: this->_bytes )
        {
            h ^= b + 0x9E3779B9 + ( h << 6 ) + ( h >> 2 );
        }
        
        return h;
    }
    
    std::size_t Data::size() const
    {
        return this->_bytes.size();
    }
    
    std::vector< uint8_t > Data::bytes() const
    {
        return this->_bytes;
    }
    
    std::string Data::string() const
    {
        std::string s( this->_bytes.size(), 0 );
        
        memcpy( &( s[ 0 ] ), &( this->_bytes[ 0 ] ), this->_bytes.size() );
        
        return s;
    }
    
    std::vector< uint8_t > Data::copyBytes( std::size_t index, std::size_t size ) const
    {
        std::vector< uint8_t > bytes( size, 0 );
        
        this->copyBytes( &( bytes[ 0 ] ), index, size );
        
        return bytes;
    }
    
    void Data::copyBytes( uint8_t * buf, std::size_t index, std::size_t size ) const
    {
        if( size == 0 )
        {
            return;
        }
        
        if( this->_bytes.size() < index + size )
        {
            throw std::out_of_range( "Index is out of bounds: " + std::to_string( index ) );
        }
        
        memcpy( buf, &( this->_bytes[ index ] ), size );
    }
    
    void Data::append( uint8_t value )
    {
        this->_append( value );
    }
    
    void Data::append( uint16_t value )
    {
        this->_append( value );
    }
    
    void Data::append( uint32_t value )
    {
        this->_append( value );
    }
    
    void Data::append( uint64_t value )
    {
        this->_append( value );
    }
    
    void Data::append( const Data & value )
    {
        this->_append( &( value._bytes[ 0 ] ), value._bytes.size() );
    }
    
    void Data::append( const std::string & value )
    {
        this->_append( reinterpret_cast< const uint8_t * >( &( value[ 0 ] ) ), value.size() );
    }
    
    void Data::append( const std::vector< uint8_t > & value )
    {
        this->_append( &( value[ 0 ] ), value.size() );
    }
    
    void Data::_append( const uint8_t * buf, std::size_t size )
    {
        if( size == 0 )
        {
            return;
        }
        
        std::size_t n = this->_bytes.size();
        
        this->_bytes.resize( n + size, 0 );
        memcpy( &( this->_bytes[ n ] ), buf, size );
    }
    
    Data operator +( const Data & o, uint8_t value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, uint16_t value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, uint32_t value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, uint64_t value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, const Data & value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, const std::string & value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    Data operator +( const Data & o, const std::vector< uint8_t > & value )
    {
        Data data( o );
        
        data += value;
        
        return data;
    }
    
    void swap( Data & o1, Data & o2 )
    {
        using std::swap;
        
        swap( o1._bytes, o2._bytes );
    }
    
    std::ostream & operator <<( std::ostream & os, const Data & o )
    {
        os << std::to_string( o._bytes.size() ) << " bytes: [";
        
        for( const auto & b: o._bytes )
        {
            os << " "
               << std::hex
               << std::uppercase
               << std::setw( 2 )
               << std::setfill( '0' )
               << static_cast< unsigned int >( b );
        }
        
        os << " ]";
        
        return os;
    }
};
