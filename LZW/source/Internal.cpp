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
 * @file        Internal.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <LZW/Internal.hpp>

namespace LZW
{
    namespace Internal
    {
        std::unordered_map< Data, uint8_t > DictionaryForCompression()
        {
            std::unordered_map< Data, uint8_t > dict;
            
            for( std::size_t i = 0; i < 27; i++ )
            {
                dict[ static_cast< uint8_t >( i + 65 ) ] = static_cast< uint8_t >( i );
            }
            
            return dict;
        }
        
        std::unordered_map< uint8_t, Data > DictionaryForExpansion()
        {
            std::unordered_map< uint8_t, Data > dict;
            
            for( const auto & p: DictionaryForCompression() )
            {
                dict[ p.second ] = p.first;
            }
            
            return dict;
        }
    }
}
