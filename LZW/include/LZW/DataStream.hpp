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
 * @header      DataStream.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef LZW_DATA_STREAM_HPP
#define LZW_DATA_STREAM_HPP

#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <LZW/Data.hpp>

namespace LZW
{
    class DataStream
    {
        public:
            
            DataStream();
            DataStream( const Data & data );
            DataStream( const DataStream & o );
            DataStream( DataStream && o );
            ~DataStream();
            
            DataStream & operator  =( DataStream o );
            DataStream & operator +=( const Data & data );
            
            operator Data() const;
            
            Data data()              const;
            bool hasBytesAvailable() const;
            
            uint8_t  readUInt8();
            uint16_t readUInt16();
            uint32_t readUInt32();
            uint64_t readUInt64();
            Data     readData( std::size_t length );
            
            void append( const Data & value );
            
            friend void swap( DataStream & o1, DataStream & o2 );
            
        private:
            
            Data        _data;
            std::size_t _pos;
            
            void read( uint8_t * buf, std::size_t size );
            
            template< typename T >
            T read()
            {
                T v = {};
                
                this->read( reinterpret_cast< uint8_t * >( &v ), sizeof( T ) );
                
                return v;
            }
    };
}

#endif /* LZW_DATA_STREAM_HPP */
