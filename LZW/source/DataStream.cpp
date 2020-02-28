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
 * @file        DataStream.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <LZW/DataStream.hpp>

namespace LZW
{
    DataStream::DataStream():
        DataStream( Data {} )
    {}
    
    DataStream::DataStream( const Data & data ):
        _data( data ),
        _pos(  0 )
    {}
    
    DataStream::DataStream( const DataStream & o ):
        _data( o._data ),
        _pos(  o._pos )
    {}
    
    DataStream::DataStream( DataStream && o ):
        _data( std::move( o._data ) ),
        _pos(  std::move( o._pos ) )
    {}
    
    DataStream::~DataStream()
    {}
    
    DataStream & DataStream::operator =( DataStream o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    DataStream & DataStream::operator +=( const Data & data )
    {
        this->append( data );
        
        return *( this );
    }
    
    DataStream::operator Data() const
    {
        return this->_data;
    }
    
    Data DataStream::data() const
    {
        return this->_data;
    }
    
    bool DataStream::hasBytesAvailable() const
    {
        if( this->_data.size() == 0 )
        {
            return false;
        }
        
        return this->_pos < this->_data.size();
    }
    
    uint8_t DataStream::readUInt8()
    {
        return this->read< uint8_t >();
    }
    
    uint16_t DataStream::readUInt16()
    {
        return this->read< uint16_t >();
    }
    
    uint32_t DataStream::readUInt32()
    {
        return this->read< uint32_t >();
    }
    
    uint64_t DataStream::readUInt64()
    {
        return this->read< uint64_t >();
    }
    
    Data DataStream::readData( std::size_t length )
    {
        return this->_data.copyBytes( this->_pos, length );
    }
    
    void DataStream::append( const Data & data )
    {
        this->_data += data;
    }
    
    void DataStream::read( uint8_t * buf, std::size_t size )
    {
        if( size == 0 )
        {
            return;
        }
        
        if( this->_pos < this->_data.size() + size )
        {
            this->_data.copyBytes( buf, this->_pos, size );
            
            this->_pos += size;
        }
        else
        {
            throw std::out_of_range( "Invalid read - Not enough data available" );
        }
    }
    
    void swap( DataStream & o1, DataStream & o2 )
    {
        using std::swap;
        
        swap( o1._data, o2._data );
        swap( o1._pos,  o2._pos );
    }
};
