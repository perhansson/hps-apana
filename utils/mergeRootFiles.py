#!/usr/bin/env python

import sys, os, string, shutil, re


#
# compose the root Macro
#
#___________________________________________________________________
def composeRootMacro(fileList):
    """Composes the root macro."""

    
    macro1 = """
#include <string.h>
#include \"TChain.h\"
#include \"TFile.h\"
#include \"TH1.h\"
#include \"TTree.h\"
#include \"TKey.h\"
#include \"Riostream.h\"

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist );


void hadd() {
"""

    macro2 = "  Target = TFile::Open(\"%s\", \"RECREATE\" );\n" % outFileName
    macro2 += "  FileList = new TList();\n"
    for file in fileList:
        macro2 += "  FileList->Add( TFile::Open(\"%s\") );\n" % file
        macro2 += "  cout << \"Added File: %s to ouput file %s\" << endl;\n" % (file,outFileName)

    macro3 = """
    MergeRootfile( Target, FileList );

}   

void OrderFile(TList* l) {
  int longest = -1;
  TObject* longestobj = 0;
  TIter nextkey( l );
  while ( (obj = (TKey*)nextkey())) {
    if ( obj->IsA()->InheritsFrom( \"TFile\" ) ) {
	  TFile *f = (TFile*)obj;
	  TList* curlist  = f->GetListOfKeys();
	  if(curlist->GetEntries()>longest) {
	    longest = curlist->GetEntries();
		longestobj = obj;
	  }
	}

  }
  if(longestobj==0) {
    std::cout << \" The longest tfile could not be found: \" << longest << std::endl; 
    exit(0);
  }
  assert(longest>0);

  std::cout << \" The longest tfile is \" << longestobj->GetName() << \" with entries: \" << longest << std::endl; 

  l->Remove(longestobj);
  l->AddFirst(longestobj);

  return;
  
}



void MergeRootfile( TDirectory *target, TList *sourcelist ) {

    TString path( (char*)strstr( target->GetPath(), \":\" ) );
    path.Remove( 0, 2 );

	OrderFile(sourcelist);
	
    TFile *first_source = (TFile*)sourcelist->First();
    first_source->cd( path );
    TDirectory *current_sourcedir = gDirectory;

    // loop over all keys in this directory
    TChain *globChain = 0;
    TIter nextkey( current_sourcedir->GetListOfKeys() );
    TKey *key;
    while ( (key = (TKey*)nextkey())) {

        // read object from first source file
        first_source->cd( path );
        TObject *obj = key->ReadObj();
		
        if ( obj->IsA()->InheritsFrom( \"TH2\" ) ) {
            // descendant of TH2 -> merge it

                  //cout << \"Merging 2-D histogram \" << obj->GetName() << endl;
            TH2 *h21 = (TH2*)obj;

            // loop over all source files and add the content of the
            // correspondant histogram to the one pointed to by \"h21\"
            TFile *nextsource = (TFile*)sourcelist->After( first_source );
            while ( nextsource ) {

                // make sure we are at the correct directory level by cd'ing to path
                nextsource->cd( path );
                TH2 *h22 = (TH2*)gDirectory->Get( h21->GetName() );
                if ( h22 ) {
                    h21->Add( h22 );
                    delete h22; // don't know if this is necessary, i.e. if 
                        // h22 is created by the call to gDirectory above.
                }

                nextsource = (TFile*)sourcelist->After( nextsource );
            }
        }
        else if ( obj->IsA()->InheritsFrom( \"TH1\" ) ) {
            // descendant of TH1 -> merge it

                  //cout << \"Merging 1-D histogram \" << obj->GetName() << endl;
            TH1 *h1 = (TH1*)obj;

            // loop over all source files and add the content of the
            // correspondant histogram to the one pointed to by \"h1\"
            TFile *nextsource = (TFile*)sourcelist->After( first_source );
            while ( nextsource ) {

                // make sure we are at the correct directory level by cd'ing to path
                nextsource->cd( path );
                TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );
                if ( h2 ) {
                    h1->Add( h2 );
                    delete h2; // don't know if this is necessary, i.e. if 
                        // h2 is created by the call to gDirectory above.
                }

                nextsource = (TFile*)sourcelist->After( nextsource );
            }
        }
        else if ( obj->IsA()->InheritsFrom( \"TTree\" ) ) {

            // loop over all source files create a chain of Trees \"globChain\"
            const char* obj_name= obj->GetName();

            globChain = new TChain(obj_name);
            globChain->Add(first_source->GetName());
            TFile *nextsource = (TFile*)sourcelist->After( first_source );
            //      const char* file_name = nextsource->GetName();
            // cout << \"file name  \" << file_name << endl;
     while ( nextsource ) {
     	  
       globChain->Add(nextsource->GetName());
       nextsource = (TFile*)sourcelist->After( nextsource );
     }

    } else if ( obj->IsA()->InheritsFrom( \"TDirectory\" ) ) {
      // it's a subdirectory

      cout << \"Found subdirectory \" << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile( newdir, sourcelist );

    } else {

      // object is of no type that we know or can handle
      cout << \"Unknown object type, name: \" 
           << obj->GetName() << \" title: \" << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is \"in\" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by \"target->Write()\" below
    if ( obj ) {
      target->cd();

      //!!if the object is a tree, it is stored in globChain...
	if(obj->IsA()->InheritsFrom( \"TTree\" ))
	  globChain->Write( key->GetName() );
	else
	obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->Write();

}
"""

    return macro1+macro2+macro3
    


#_________________________________________________________________
#
# START MAIN PROGRAM
#

#
# quick check
#
if len(sys.argv) < 1:
    raise "Wrong usage!! Correct syntax is: mergeRootFiles.py fileNameXX.TYPE.root [outFileName]"
    #raise "Wrong usage!! Correct syntax is: mergeRootFiles.py fileName_xx.root [outFileName]"

fileName = sys.argv[1]

type = sys.argv[2]


if len(sys.argv) > 3:
    outFileName = sys.argv[3]
else:
    outFileName = fileName + "COMB." + type + ".root"



dir = os.listdir(os.getcwd())
#regex = re.compile(fileName+"_\d*\.AAN.root")
regex = re.compile("^"+fileName+"\d*\."+type+".root")
fileList=[]
#
# start loop over input files
#
for file in dir:
    print "Testing file ",file
    if re.search(regex,file):
        if re.search(fileName+"."+type,file):
           continue
        fileList.append(file)
if fileList==[]:
    raise "No input files found!"

#
# write root macro
#
macroFile=open("hadd.C", "w")
macroFile.write(composeRootMacro(fileList))
macroFile.close()

#
# ... and add
#
os.system("root -l -n -b -q hadd.C")
#os.remove("hadd.C")


print "\n################################"
print "---> Added ", len(fileList)," files to output file", outFileName,"\n"



    
