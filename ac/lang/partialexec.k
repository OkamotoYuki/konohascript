/****************************************************************************
 * KONOHA ASSURANCE CASE
 *  written by Kimio Kuramitsu  twitter: @konohakun 
 ***************************************************************************/

int readnum(int seq) {
	if(seq == 0) {
		ins = new InputStream("seq.txt");
		seq = ins.readnum(); // type error
		ins.close();
	}
	else {
		seq += 1;
	}
	return seq;
}

assure "PartialExecution" {
	assert readnum(1) == 2;
}

assure "PartialExecution" {
	try {
		n = readnum(0);
	}
	catch(Script!! e) {
		print e;
	}
}


