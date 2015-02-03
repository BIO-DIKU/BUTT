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
    cerr<<"TestFasta::runTests: Test 1 "<<(test1()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 2 "<<(test2()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 3 "<<(test3()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 4 "<<(test4()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 5 "<<(test5()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 6 "<<(test6()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 7 "<<(test7()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 8 "<<(test8()?"succesful":"failed")<<endl;
    cerr<<"TestFasta::runTests: Test 9 "<<(test9()?"succesful":"failed")<<endl;
    return true;
}

bool TestFasta::test1()
{
    try{
    Fasta fasta(fastaDirectory+"/test1.fasta");
    FastaEntry e1 = fasta.nextEntry();
    FastaEntry e2 = fasta.nextEntry();

    BUTT_ASSERT_FALSE(false, "EOF not reached");
    //BUTT_ASSERT_FALSE(fasta.hasNextEntry(), "EOF not reached");


    BUTT_ASSERT_EQUALS("1 K#Bacteria;P#Proteobacteria", e1.header, "First header invalid (was: "+e1.header+")"  );
    BUTT_ASSERT_EQUALS("1 K#Bacteria;P#Proteobacteria", e2.header, "Second header invalid (was: "+e2.header+")"  );
    BUTT_ASSERT_EQUALS("ATCGU atcgu", e1.sequence, "Second sequence invalid (was: "+e1.sequence+")"  );
    BUTT_ASSERT_EQUALS("atcgu", e2.sequence, "Second sequence invalid (was: "+e2.sequence+")"  );
    }catch(FastaException e){
        std::cout<<"Exception caught: "<<e.exceptionMsg<<endl;
        return false;
    }
    return true;
}

bool TestFasta::test2()
{

    return false;
}

bool TestFasta::test3()
{

    return false;
}

bool TestFasta::test4()
{

    return false;
}

bool TestFasta::test5()
{

    return false;
}

bool TestFasta::test6()
{

    return false;
}

bool TestFasta::test7()
{

    return false;
}

bool TestFasta::test8()
{

    return false;
}

bool TestFasta::test9()
{

    return false;
}
