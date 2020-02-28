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
 * @file        main.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <iostream>
#include <exception>
#include <LZW/LZW.hpp>

int main( int argc, char * argv[] )
{
    ( void )argc;
    ( void )argv;
    
    try
    {
        LZW::Data original     = std::string( "TOBEORNOTTOBEORTOBEORNOT" );
        LZW::Data compressed   = LZW::Compress( original );
        LZW::Data uncompressed = LZW::Expand( compressed );
        
        std::cout << "Original:            " << original              << std::endl;
        std::cout << "Compressed:          " << compressed            << std::endl;
        std::cout << "Uncompressed:        " << uncompressed          << std::endl;
        std::cout << "----------"                                     << std::endl;
        std::cout << "Original string:     " << original.string()     << std::endl;
        std::cout << "Uncompressed string: " << uncompressed.string() << std::endl;
        std::cout << "----------"                                     << std::endl;
            
        if( uncompressed != original )
        {
            std::cout << "Error: " << original.string() << " != " << uncompressed.string() << std::endl;
            
            return -1;
        }
    }
    catch( const std::exception & e )
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
        
        return -1;
    }
    catch( ... )
    {
        std::cout << "Caught unknown exception" << std::endl;
        
        return -1;
    }
    
    return 0;
}
