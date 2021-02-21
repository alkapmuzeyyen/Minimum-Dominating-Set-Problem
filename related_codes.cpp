#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

int each_vertex_200_times(int i)
{
    if (i<2000)
        return 6;
    else if (i < 4000)
        return 7;
    else if (i < 6000)
        return 8;
    else if (i < 8000)
        return 9;
    else
        return 10;
}


void generate_black_box()
{
    srand(time(NULL));
    for (int i_10000 = 0; i_10000 < 10000; i_10000++)
    {
        int vertex = each_vertex_200_times(i_10000);
        int edge = 10;
        int edge_counter = 0;
        vector<vector<int>> mat(vertex, vector<int> (vertex));
        vector<vector<int>> mat2(vertex, vector<int> (vertex));
        
        
        while (edge != edge_counter)
        {
            // generate 2 vertices
            int random_v1 = rand() % vertex;
            int random_v2 = rand() % vertex;
            
            // put an edge between them
            if(mat[random_v1][random_v2] == 0 && random_v1 != random_v2)
            {
                mat[random_v1][random_v2] = 1;
                mat[random_v2][random_v1] = 1;
                
                mat2[random_v1][random_v2] = 1;
                mat2[random_v2][random_v1] = 1;
                edge_counter++;
            }
        }
        
        ofstream out;
        string out_file = "/Users/muzeyyenalkap/Downloads/outputs2/" + to_string(i_10000) + "sample.txt";
        out.open(out_file);
        out << vertex << " " << (edge*2) << endl;
        
        for (int row =0; row<vertex; row++) {
            for (int col=0; col<vertex; col++) {
                if (mat[row][col] == 1 && row != col)
                {
                    out << (to_string(row+1) + " " + to_string(col+1))<< endl;
                }
            }
        }
        out.close();
        
        ofstream out2;
        string out_file2 = "/Users/muzeyyenalkap/Downloads/outputs2/"+ to_string(i_10000) + "sample_exact.txt";
        out2.open(out_file2);
        //out2 << vertex << "\t" << (edge) << endl;
        
        out2 << vertex;
        for (int u=1; u<vertex+1; u++) {
            out2 << " "<< u;
        }
        out2<< endl;
        
        for (int row =0; row<vertex; row++) {
            
            out2 << (row+1) ;
            for (int col=0; col<vertex; col++) {
                
                out2 << " " << mat2[row][col];
            }
            out2 << endl;
        }
        
        out2.close();
    }
}

void convert_inputs()
{
    // sample inputlardan bizim formata dönüştür
    int iii = 9;
    int vertex = 150;
    int edge = 250;
    vector<vector<int>> mat(vertex, vector<int> (vertex));
    ifstream in;
    string file_name ="/Users/muzeyyenalkap/Downloads/ProblemInstances/T1/V150E250/9/Test/Problem.dat_150_250_9";
    in.open(file_name.c_str());
    
    int edge_counter = 305;
    string line;
    while ( edge_counter != 0)
    {
        getline(in,line);
        edge_counter--;
    }
    
    ofstream out;
    string out_file = "/Users/muzeyyenalkap/Downloads/outputs_v150_e250/" + to_string(iii) + "sample.txt";
    out.open(out_file);
    out << vertex << " " << (edge*2) << endl;
    
    int col=1, row=1;
    
    while ( getline(in,line))
    {
        for (int l=0; l<line.length(); l+=2)
        {
            if (line[l] == '1' && row != col)
            {
                out << (to_string(row) + " " + to_string(col))<< endl;
            }
            col ++;
        }
        row++;
        col = 1;
    }
    out.close();
}

void compare_exact_and_heuristic()
{
    ifstream in_exact, in_heu;
    string exact_name = "/Users/muzeyyenalkap/Downloads/cs301_project/exact_results.txt";
    string heu_name = "/Users/muzeyyenalkap/Downloads/cs301_project/greedy_results.txt";
    
    in_exact.open(exact_name.c_str());
    in_heu.open(heu_name.c_str());
    
    double result_vert = 0;
    double result_time = 0;
    double w_e, w_h;
    vector<double> quality;
    vector<double> time;
    double ratio_vertex = 0, ratio_time = 0, mean_vert, mean_time;
    for (int y=0; y<5; y++) {
        for (int i=0; i<2000; i++)
        {
            in_exact >> w_e;
            in_heu >> w_h;
            
            ratio_vertex = w_e / w_h;
            result_vert += ratio_vertex;
            
            in_exact >> w_e;
            in_heu >> w_h;
            
            ratio_time = w_e / w_h;
            result_time += ratio_time;
        }
        mean_vert = result_vert / 2000;
        mean_time = result_time / 2000;
        quality.push_back(mean_vert);
        time.push_back(mean_time);
        result_vert = 0;
        result_time = 0;
    }
    
    ofstream out;
    string output_name = "/Users/muzeyyenalkap/Downloads/cs301_project/comparison_results.txt";
    out.open(output_name.c_str());
    
    for (int v=0; v < quality.size(); v++)
    {
        out << "Number of vertices = " << (v+6) << endl;
        out << quality[v] << " " << time[v] << endl;
    }
}
void find_fails()
{
    
    ifstream in_exact, in_heu;
    string exact_name = "/Users/muzeyyenalkap/Downloads/cs301_project/exact_results.txt";
    string heu_name = "/Users/muzeyyenalkap/Downloads/cs301_project/greedy_results.txt";
    
    in_exact.open(exact_name.c_str());
    in_heu.open(heu_name.c_str());
    
    
    double w_e, w_h;
    vector<double> quality;
    vector<double> time;
    double ratio_vertex = 0, ratio_time = 0, mean_vert, mean_time;
    for (int y=0; y<5; y++) {
        for (int i=0; i<2000; i++)
        {
            in_exact >> w_e;
            in_heu >> w_h;
            
            if (w_e != w_h) {
                cout << (y*2000) + i <<  " " <<w_e << " " << w_h << endl;
            }
            
            in_exact >> w_e;
            in_heu >> w_h;
            
        }
    }
    
}
int main()
{
    find_fails();
    
    return 0;
}
