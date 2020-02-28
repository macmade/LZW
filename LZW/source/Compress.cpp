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
 * @file        Compress.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <LZW/Compress.hpp>
#include <LZW/DataStream.hpp>
#include <LZW/Internal.hpp>
#include <iostream>
#include <limits>
#include <exception>

namespace LZW
{
    Data Compress( const Data & data )
    {
        if( data.size() < 2 )
        {
            return data;
        }
        
        uint8_t                              code;
        DataStream                           output;
        DataStream                           input   = data;
        std::unordered_map< Data, uint8_t >  dict    = Internal::DictionaryForCompression();
        Data                                 current = input.readUInt8();
        
        if( dict.find( current ) == dict.end() )
        {
            throw std::runtime_error( "Invalid input - Not in dictionary" );
        }
        
        do
        {
            uint8_t byte   = input.readUInt8();
            Data    lookup = current + byte;
            
            if( dict.find( lookup ) != dict.end() )
            {
                current = lookup;
            }
            else
            {
                if( dict.find( current ) == dict.end() )
                {
                    throw std::runtime_error( "Invalid input - Not in dictionary" );
                }
                
                code = dict[ current ];
                
                std::cout << "> Out: " << current.string() << " => " << std::to_string( code ) << std::endl;
                
                output += code;
                
                if( dict.size() < std::numeric_limits< uint8_t >::max() )
                {
                    std::cout << "+ Add: " << lookup.string() << " => " << std::to_string( dict.size() + 1 ) << std::endl;
                    
                    dict[ lookup ] = static_cast< uint8_t >( dict.size() + 1 );
                }
                
                current = byte;
            }
        }
        while( input.hasBytesAvailable() );
        
        if( dict.find( current ) == dict.end() )
        {
            throw std::runtime_error( "Invalid input - Not in dictionary" );
        }
        
        code = dict[ current ];
        
        std::cout << "> Out: " << current.string() << " => " << std::to_string( code ) << std::endl;
        
        output += code;
        
        std::cout << "----------" << std::endl;
        
        return output;
    }
}
