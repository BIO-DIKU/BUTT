#include "TestFasta.h"

#include <iostream>
#include <string>

#include "Fasta.h"
#include "TestHelper.h"

using namespace std;

TestFasta::TestFasta(const string &fasta_test_directory): fastaDirectory(fasta_test_directory)
{
}

bool TestFasta::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestFasta test 1", test1());
    BUTT_RUN_TEST("TestFasta test 2", test2());
    BUTT_RUN_TEST("TestFasta test 3", test3());
    BUTT_RUN_TEST("TestFasta test 4", test4());
    BUTT_RUN_TEST("TestFasta test 5", test5());
    BUTT_RUN_TEST("TestFasta test 6", test6());
    BUTT_RUN_TEST("TestFasta test 7", test7());
    BUTT_RUN_TEST("TestFasta test 8", test8());
    BUTT_RUN_TEST("TestFasta test 9", test9());
    BUTT_POST_TESTS();
}

bool TestFasta::test1()
{
    Fasta fasta(fastaDirectory+"/test1.fasta");
    FastaEntry e1 = fasta.nextEntry();
    FastaEntry e2 = fasta.nextEntry();
    BUTT_ASSERT_FALSE(fasta.hasNextEntry(), "EOF not reached");

    BUTT_ASSERT_EQUALS("1 K#Bacteria;P#Proteobacteria", e1.header, "First header invalid (was: "+e1.header+")"  );
    BUTT_ASSERT_EQUALS("1 K#Bacteria;P#Proteobacteria", e2.header, "Second header invalid (was: "+e2.header+")"  );
    BUTT_ASSERT_EQUALS("ATCGU atcgu", e1.sequence, "Second sequence invalid (was: "+e1.sequence+")"  );
    BUTT_ASSERT_EQUALS("atcgu", e2.sequence, "Second sequence invalid (was: "+e2.sequence+")"  );
    return true;
}

bool TestFasta::test2()
{

    Fasta fasta(fastaDirectory+"/test2.fasta");
    FastaEntry e1 = fasta.nextEntry();
    FastaEntry e2 = fasta.nextEntry();

    BUTT_ASSERT_EQUALS("1", e1.header, "First header invalid (was: "+e1.header+")"  );
    BUTT_ASSERT_EQUALS("2", e2.header, "Second header invalid (was: "+e2.header+")"  );
    BUTT_ASSERT_EQUALS("at cg ATCG", e1.sequence, "Second sequence invalid (was: "+e1.sequence+")"  );
    BUTT_ASSERT_EQUALS("atcg", e2.sequence, "Second sequence invalid (was: "+e2.sequence+")"  );
    return true;
}

bool TestFasta::test3()
{
    Fasta fasta(fastaDirectory+"/test3.fasta");
    FastaEntry e1 = fasta.nextEntry();

    BUTT_ASSERT_EQUALS("1>2", 	e1.header, "First header invalid (was: "+e1.header+")"  );
    BUTT_ASSERT_EQUALS("AT>CG", e1.sequence, "Second sequence invalid (was: "+e1.sequence+")"  );
    return true;
}

bool TestFasta::test4()
{
    try{
        Fasta fasta(fastaDirectory+"/test4.fasta");
        FastaEntry e1 = fasta.nextEntry();

        BUTT_ASSERT_FALSE(true, "Exception wasnt thrown" );
    }catch(FastaException e){
        BUTT_ASSERT_TRUE(true, "Exception was thrown");
        return true;
    }
    return false;
}

bool TestFasta::test5()
{
    try{
        Fasta fasta(fastaDirectory+"/test5.fasta");
        FastaEntry e1 = fasta.nextEntry();

        BUTT_ASSERT_FALSE(true, "Exception wasnt thrown" );
    }catch(FastaException e){
        BUTT_ASSERT_TRUE(true, "Exception was thrown");
        return true;
    }
    return false;
}

bool TestFasta::test6()
{
    try{
        Fasta fasta(fastaDirectory+"/test6.fasta");
        FastaEntry e1 = fasta.nextEntry();

        BUTT_ASSERT_FALSE(true, "Exception wasnt thrown" );
    }catch(FastaException e){
        BUTT_ASSERT_TRUE(true, "Exception was thrown");
        return true;
    }
    return false;
}

bool TestFasta::test7()
{
    try{
        Fasta fasta(fastaDirectory+"/test7.fasta");
        FastaEntry e1 = fasta.nextEntry();

        BUTT_ASSERT_FALSE(true, "Exception wasnt thrown" );
    }catch(FastaException e){
        BUTT_ASSERT_TRUE(true, "Exception was thrown");
        return true;
    }
    return false;

}

bool TestFasta::test8()
{
    try{
        Fasta fasta(fastaDirectory+"/test8.fasta");
        BUTT_ASSERT_FALSE(fasta.hasNextEntry(), "Fasta thinks there is an entry");
        return true;
    }catch(FastaException e){
        BUTT_ASSERT_FALSE(true, "Exception was thrown");
        return false;
    }
    return true;
}

bool TestFasta::test9()
{

    try{
        Fasta fasta(fastaDirectory+"/test9.fasta");
        FastaEntry e1 = fasta.nextEntry();

        BUTT_ASSERT_FALSE(true, "Exception wasnt thrown" );
    }catch(FastaException e){
        BUTT_ASSERT_TRUE(true, "Exception was thrown");
        return true;
    }
    return false;
}
