#include "include/testtask12.h"
using namespace std;
void TestTask12::test1(){
    Graph g(5);
    g.add_edge(0,1,1);
    g.add_edge(1,2,1);
    g.add_edge(0,3,1);
    g.add_edge(1,4,1);
    g.add_edge(3,4,1);
    string prog_ans = task12::input(g);
    string ans = "#FFFF00 #FF0000 #FFFF00 #FF0000 #FFFF00 ";
    //cout << prog_ans << '\n';
    QCOMPARE(ans, prog_ans);

}

void TestTask12::problemtest(){
    Graph gg(8);
    gg.add_edge(0,4,1);
    gg.add_edge(1,5,1);
    gg.add_edge(2,6,1);
    gg.add_edge(3,7,1);
    gg.add_edge(0,5,1);
    gg.add_edge(1,7,1);
    gg.add_edge(3,4,1);
    string prog_ans = task12::input(gg);
    string ans = "#FF0000 #FF0000 #FF0000 #FF0000 #FFFF00 #FFFF00 #FFFF00 #FFFF00 ";
    //cout << prog_ans << '\n';
    QCOMPARE(ans, prog_ans);
}
void TestTask12::test20(){
    Graph g(20);
    string prog_ans = task12::input(g);
    //cout << prog_ans;
    string ans = "#FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 #FF0000 ";
    QCOMPARE(ans, prog_ans);
}
void TestTask12::startest(){
    Graph g(11);
    g.add_edge(0,1,1); g.add_edge(0,2,1);
    g.add_edge(0,3,1); g.add_edge(0,4,1);
    g.add_edge(0,5,1); g.add_edge(0,6,1);
    g.add_edge(0,7,1); g.add_edge(0,8,1);
    g.add_edge(0,9,1); g.add_edge(0,10,1);
    string prog_ans = task12::input(g);
    string ans = "#FF0000 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 #FFFF00 ";
    QCOMPARE(ans, prog_ans);
}
void TestTask12::treetest(){
    Graph g(7);
    g.add_edge(0,1,1);
    g.add_edge(0,2,1);
    g.add_edge(1,3,1);
    g.add_edge(1,4,1);
    g.add_edge(1,5,1);
    g.add_edge(2,6,1);
    string prog_ans = task12::input(g);
    string ans = "#FFFF00 #FF0000 #FF0000 #FFFF00 #FFFF00 #FFFF00 #FFFF00 ";
    //cout << prog_ans;
    QCOMPARE(ans, prog_ans);
}
void TestTask12::squaretest(){
    Graph g(4);
    g.add_edge(0,1,1);
    g.add_edge(0,2,1);
    g.add_edge(0,3,1);
    g.add_edge(1,2,1);
    g.add_edge(2,3,1);
    g.add_edge(1,3,1);
    string prog_ans = task12::input(g);
    string ans = "#FF0000 #FFFF00 #00BFFF #00FF00 ";
    //cout << prog_ans;
    QCOMPARE(ans, prog_ans);
}
void TestTask12::pantest(){
    Graph g(20);
    for(int i = 0; i < 20; ++i){
        for(int j = i; j < 20; ++j){
            g.add_edge(i, j, 1);
        }
    }
    string prog_ans = task12::input(g);
    map<int, string> colors{{0, "Transparent"}, {1, "#FF0000"}, {2, "#FFFF00"}, {3, "#00BFFF"},
                            {4, "#00FF00"}, {5, "#F0E68C"}, {6, "#EE82EE"}, {7, "#DEB887"}, {8, "#808000"},
                            {9, "#B0E0E6"}, {10, "#FFE4E1"}, {11, "#A9A9A9"}, {12, "#F08080"}, {13, "#C71585"}, {14, "#FFA500"}, {15, "#BDB76B"},
                            {16, "#4B0082"}, {17, "#BC8F8F"}, {18, "#7FFFD4"}, {19, "#008B8B"}, {20, "#800000"},  {21, "#8B4513"}};
    string ans = "";
    for(int i = 1; i <=20; ++i){
        ans += colors[i];
        ans += " ";
    }
    //cout << prog_ans << '\n' << ans;
    QCOMPARE(ans, prog_ans);
}
Q_DECLARE_METATYPE(TestTask12)
#include "testtask12.moc"
