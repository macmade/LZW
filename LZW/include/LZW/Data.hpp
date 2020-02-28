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
 * @header      Data.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef LZW_DATA_HPP
#define LZW_DATA_HPP

#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

namespace LZW
{
    class Data
    {
        public:
            
            Data();
            Data( uint8_t value );
            Data( uint16_t value );
            Data( uint32_t value );
            Data( uint64_t value );
            Data( const std::string & value );
            Data( const std::vector< uint8_t > & value );
            Data( const Data & o );
            Data( Data && o );
            ~Data();
            
            Data & operator =( Data o );
            
            bool operator ==( const Data & o ) const;
            bool operator !=( const Data & o ) const;
            
            bool operator  >( const Data & o ) const;
            bool operator  <( const Data & o ) const;
            bool operator >=( const Data & o ) const;
            bool operator <=( const Data & o ) const;
            
            Data & operator +=( uint8_t value );
            Data & operator +=( uint16_t value );
            Data & operator +=( uint32_t value );
            Data & operator +=( uint64_t value );
            Data & operator +=( const Data & value );
            Data & operator +=( const std::string & value );
            Data & operator +=( const std::vector< uint8_t > & value );
            
            uint8_t operator []( std::size_t index ) const;
            
            operator std::vector< uint8_t >() const;
            operator std::string()            const;
            
            std::size_t            hash()   const;
            std::size_t            size()   const;
            std::vector< uint8_t > bytes()  const;
            std::string            string() const;
            
            std::vector< uint8_t > copyBytes( std::size_t index, std::size_t size )                const;
            void                   copyBytes( uint8_t * buf, std::size_t index, std::size_t size ) const;
            
            void append( uint8_t value );
            void append( uint16_t value );
            void append( uint32_t value );
            void append( uint64_t value );
            void append( const Data & value );
            void append( const std::string & value );
            void append( const std::vector< uint8_t > & value );
            
            friend Data operator +( const Data & o, uint8_t value );
            friend Data operator +( const Data & o, uint16_t value );
            friend Data operator +( const Data & o, uint32_t value );
            friend Data operator +( const Data & o, uint64_t value );
            friend Data operator +( const Data & o, const Data & value );
            friend Data operator +( const Data & o, const std::string & value );
            friend Data operator +( const Data & o, const std::vector< uint8_t > & value );
            
            friend void swap( Data & o1, Data & o2 );
            
            friend std::ostream & operator <<( std::ostream & os, const Data & o );
            
        private:
            
            std::vector< uint8_t > _bytes;
            
            void _append( const uint8_t * buf, std::size_t size );
            
            template< typename T >
            void _append( T value )
            {
                this->_append( reinterpret_cast< uint8_t * >( &value ), sizeof( T ) );
            }
    };
}

namespace std
{
    template<>
    struct hash< LZW::Data >
    {
        std::size_t operator()( const LZW::Data & data ) const
        {
            return data.hash();
        }
    };
}

#endif /* LZW_DATA_HPP */
