#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#ifndef __GNUC__
#include <io.h>
#else
#include <unistd.h>
#endif

#include <entriesblk.h>
#include <iostream.h>
#include <treekeyidx.h>
#include <rawgenbook.h>

#ifndef O_BINARY
#define O_BINARY 0
#endif

void printTree(TreeKeyIdx treeKey, TreeKeyIdx *target = 0, int level = 1) {
  if (!target)
    target = &treeKey;
  
  unsigned long currentOffset = target->getOffset();
  cout << ((currentOffset == treeKey.getOffset()) ? "==>" : "");
  for (int i = 0; i < level; i++) cout << "\t";
  cout << treeKey.getLocalName() << "/\n";
  if (treeKey.firstChild()) {
    printTree(treeKey, target, level+1);
    treeKey.parent();
  }
  if (treeKey.nextSibling())
    printTree(treeKey, target, level);
}

void setkey (TreeKeyIdx * treeKey, char* keybuffer) {
  char* tok = strtok(keybuffer, "/");
  while (tok) {
    bool foundkey = false;
    if (treeKey->hasChildren()) {
      treeKey->firstChild();
      if (!strcmp(treeKey->getLocalName(), tok)) {
	foundkey = true;
      } else {
	while (treeKey->nextSibling()) {
	  if (treeKey->getLocalName()) {
	    if (!strcmp(treeKey->getLocalName(), tok)) {
	      foundkey = true;
	    }
	  }
	}
      }
      if (!foundkey) {
	treeKey->append();
	treeKey->setLocalName(tok);
	treeKey->save();	    
      }
    }
    else {
      treeKey->appendChild();
      treeKey->setLocalName(tok);
      treeKey->save();
    }
    
    //DEBUG      cout << treeKey->getLocalName() << " : " << tok << endl;
    
    tok = strtok(NULL, "/");
    
  }
}

int readline(FILE* infile, char* linebuffer) {
  signed char c;
  char* lbPtr = linebuffer;
  while ((c = fgetc(infile)) != EOF) {
    *lbPtr++ = c;
    if (c == 10) {
      *lbPtr = 0;
      return (strlen(linebuffer));
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  
  const char * helptext ="imp2gbs 1.0 General Book module creation tool for the SWORD Project\n  usage:\n   %s <filename> [modname]\n";
  
  signed long i = 0;
  char* keybuffer = new char[2048];
  char* entbuffer = new char[1048576];
  char* linebuffer = new char[1048576];
  char modname[16];
  
  if (argc > 2) {
    strcpy (modname, argv[2]);
  }
  else if (argc > 1) {
    for (i = 0; (i < 16) && (argv[1][i]) && (argv[1][i] != '.'); i++) {
      modname[i] = argv[1][i];
    }
    modname[i] = 0;
  }
  else {
    fprintf(stderr, helptext, argv[0]);
    exit(-1);
  }
  
  FILE *infile;
  infile = fopen(argv[1], "r");
  
  TreeKeyIdx * treeKey;
  RawGenBook *book;
  
  // Do some initialization stuff
  TreeKeyIdx::create(modname);
  treeKey = new TreeKeyIdx(modname);
  RawGenBook::createModule(modname);
  delete treeKey;
  book = new RawGenBook(modname);
  //DEBUG  TreeKeyIdx root = *((TreeKeyIdx *)((SWKey *)(*book)));
  treeKey = ((TreeKeyIdx *)((SWKey *)(*book)));
  
  while (readline(infile, linebuffer)) {
    if (!strncmp(linebuffer, "$$$", 3)) {
      if (strlen(keybuffer) && strlen(entbuffer)) {
	cout << keybuffer << endl;
	treeKey->root();
	setkey(treeKey, keybuffer);
	book->setentry(entbuffer, strlen(entbuffer));
      }
      linebuffer[strlen(linebuffer) - 1] = 0;
      strcpy (keybuffer, linebuffer + 3);
      *entbuffer = 0;
    }
    else {
      strcat (entbuffer, linebuffer);
    }
  }

  //handle final entry
  if (strlen(keybuffer) && strlen(entbuffer)) {
    cout << keybuffer << endl;
    treeKey->root();
    setkey(treeKey, keybuffer);
    book->setentry(entbuffer, strlen(entbuffer));
  }
  
  //DEBUG  printTree(root, treeKey);
  
  delete book;
  delete [] keybuffer;
  delete [] linebuffer;
  delete [] entbuffer;

  return 0;
}



