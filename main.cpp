#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "DisciplinieGui.h"
#include "ui.h"
#include <iostream>
using std::cout;
using std::endl;
void testAll() {
	TesteDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	DisciplinaValidator val;
	DisciplinaRepositoryFile repoFile("fisier.txt");
	DisciplinaStore srv{ repoFile,val };
	DisciplineStoreGUI gui{ srv };
    gui.show();
    return a.exec();
}
