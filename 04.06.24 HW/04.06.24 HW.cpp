#include<windows.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class IDocument
{
public:
	virtual void DocumentOpen(ifstream& infile) = 0;
	virtual void DocumentClose(ofstream& outfile) = 0;
};

class RealDocument : public IDocument
{
	string documentName;
public:
	RealDocument(const string& name) : documentName(name)
	{
		cout << "Create object " << documentName << ". Wait...\n";
		Sleep(3000);
	}

	void DocumentOpen(ifstream& infile) override
	{
		if (infile.is_open())
			cout << "Document " << documentName << " is open" << endl;
	}
	void DocumentClose(ofstream& outfile) override
	{
		if (!outfile.is_open())
			cout << "Document " << documentName << " is close" << endl;
	}
};

class DocumentProxy : public IDocument
{
	RealDocument* realDocument;
public:
	DocumentProxy()
	{
		realDocument = nullptr;
	}
	~DocumentProxy()
	{
		delete realDocument;
	}
	void DocumentOpen(ifstream& infile) override
	{
		if (infile.is_open())
			cout << "Document is open" << endl;
	}
	void DocumentClose(ofstream& outfile) override
	{
		if (!outfile.is_open())
			cout << "Document is close" << endl;
	}
};

void client(IDocument* p, ofstream& outfile, ifstream& infile)
{
	p->DocumentOpen(infile);
	p->DocumentClose(outfile);

}

int main()
{
	RealDocument* doc = new RealDocument("Your string here");
	IDocument* p = new DocumentProxy();
	ifstream file("Input.txt");
	ofstream file1("Input.txt");
	client(p, file1, file);

}