/*=========================================================================

 Program: ALBA (Agile Library for Biomedical Applications)
 Module: TriangulationTest
 Authors: Stefano Perticoni
 
 Copyright (c) BIC
 All rights reserved. See Copyright.txt or


 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __CPP_UNIT_TriangulationTest_H__
#define __CPP_UNIT_TriangulationTest_H__

#include "albaTest.h"

class TriangulationTest : public albaTest
{
  CPPUNIT_TEST_SUITE( TriangulationTest );
  CPPUNIT_TEST( TestConstructorDestructor );
  CPPUNIT_TEST( TestFactor );
  CPPUNIT_TEST( TestArea ); 
  CPPUNIT_TEST( TestFlipMinimize );
  CPPUNIT_TEST( TestAddTriangle );
  CPPUNIT_TEST_SUITE_END();

protected:

  void TestConstructorDestructor();
  void TestArea();
  void TestFlipMinimize();
  void TestAddTriangle();
  void TestFactor();

};

#endif