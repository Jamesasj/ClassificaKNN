#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <cstdio>
#include <cstdlib>

#define SIZE_OF_DATA 150

std::vector<unsigned> setosas;
std::vector<unsigned> versicolor;
std::vector<unsigned> virginica;

//Estrutura da iris
struct iris_data {
    double sepal_lenght;
    double sepal_width;
    double petal_lenght;
    double petal_width;
    std::string specie;
}typedef Iris;

//Split em string
void split(const std::string &s, char delim, 
            std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> split(const std::string &s, 
                                char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

//Carrega os dados de treinamento para a struct
void prepare(std::vector<Iris> &iris){

    freopen("training_data", "r", stdin);
    
    std::vector<std::string> aux;
    
    for(unsigned i = 0; i < SIZE_OF_DATA; i++){
        std::string read;
        std::cin >> read;
        aux = split(read, ',');
        
        iris[i].sepal_lenght = atof(aux[0].c_str());
        iris[i].sepal_width = atof(aux[1].c_str());
        iris[i].petal_lenght = atof(aux[2].c_str());
        iris[i].petal_width = atof(aux[3].c_str());
        iris[i].specie = aux[4];
    }
    freopen("/dev/tty", "r", stdin);
}

//lê input
void read_input(double *sepal_lenght, double *sepal_width , 
                 double *petal_lenght, double *petal_width){
    std::cout <<"Sepal lenght : ";
    std::cin  >>*sepal_lenght;
    std::cout <<"Sepal width : ";
    std::cin  >>*sepal_width;
    std::cout <<"Petal lenght : ";
    std::cin  >>*petal_lenght;
    std::cout <<"Petal width : ";
    std::cin  >>*petal_width;
}

//Cálculo da distância euclidiana
void euclidian_distance (int k , std::vector<Iris> iris,
                          double sepal_lenght, double sepal_width , 
                          double petal_lenght, double petal_width){
    
    std::multimap <double , std::string,std::less<double> > distances;
    std::multimap <double , std::string,std::less<double> > ::iterator dist_it;
    for(unsigned i = 0 ; i < SIZE_OF_DATA ; i++){
        
        double dist = sqrt(
                (iris[i].sepal_lenght - sepal_lenght) * (iris[i].sepal_lenght - sepal_lenght) +
                (iris[i].sepal_width - sepal_width) * (iris[i].sepal_width - sepal_width) +
                (iris[i].petal_lenght - petal_lenght) * (iris[i].petal_lenght - petal_lenght) +
                (iris[i].petal_width - petal_width) * (iris[i].petal_width - petal_width)
            );
        //std::cout << "value of dist " << dist <<std::endl; 
        distances.insert( std::pair <double, std::string > (dist, iris[i].specie));
    }
    
    unsigned i;
    unsigned RATE[3] = {0};
    for(dist_it = distances.begin(), i = 0 ; 
            i < k;
            dist_it++, i++)
    {
        if(dist_it->second == "Iris-setosa"){RATE[0]++; }
        else if(dist_it->second == "Iris-versicolor"){RATE[1]++; }
        else if(dist_it->second == "Iris-virginica"){RATE[2]++; }
    }       
    if((RATE[0] > RATE[1])and(RATE[0] > RATE[2])) 
        {
            //std::cout <<"Classified as iris-setosa";
            setosas.push_back(1);
        }
    else if((RATE[1] > RATE[0])and(RATE[1] > RATE[2])) 
        {
            //std::cout <<"Classified as iris-versicolor";
            versicolor.push_back(1);
        }
    else if((RATE[2] > RATE[0])and(RATE[2] > RATE[1])) 
        {
            //std::cout <<"Classified as iris-virginica";
            virginica.push_back(1);
        }
}

//Check se K é par ou impar.
bool check_K_value (int k){
    if(!(k&1)){
        std::cout << "Even value is not valid.\n";
        return false;
    }
    std::cout <<"K value is ok\n";
    return true;
}

double max (double a, double b){ if (a > b) return a; return b; }
double min (double a, double b){ if (a < b) return a; return b; }

void calculatePrecision (unsigned a, unsigned b, unsigned c){
    
    double amt1 = (min(a, 50) / max(a,50)); 
    double amt2 = (min(b, 50) / max(b,50)); 
    double amt3 = (min(c, 50) / max(c,50)); 
    
    printf("%.5lf%%\n" , (amt1 + amt2 + amt3) / 3 * 100);
    
}

int main(int argc, char* argv[]){
    
    std::vector<Iris> iris(150);
    
    double sepal_lenght;
    double sepal_width;
    double petal_lenght;
    double petal_width;
    
    unsigned queries = 1;
    int K ;
    
    prepare(iris);
    		
    K = std::stoi(argv[1]); 
    while(queries--){

        freopen(argv[2] , "r" , stdin);
        std::vector<std::string> aux;
        for(unsigned i = 0; i < 50; i++){
            std::string read;
            std::cin >> read;
            aux = split(read, ',');
        
            sepal_lenght = atof(aux[0].c_str());
            sepal_width  = atof(aux[1].c_str());
            petal_lenght = atof(aux[2].c_str());
            petal_width  = atof(aux[3].c_str());
            
            std::cout << sepal_lenght << " "
            << sepal_width << " "
            << petal_lenght << " "
            << petal_width << std::endl;
            
            euclidian_distance(K , iris, sepal_lenght, sepal_width, petal_lenght, petal_width);
        }
    }
    
        freopen("dev/tty","r",stdin);
        std::cout << "Number of setosas : " <<setosas.size() << std::endl;
        std::cout << "Number of versicolor : " <<versicolor.size() << std::endl;
        std::cout << "Number of virginica : " <<virginica.size() << std::endl;
        
        std::cout << "The Precision of algorithm is " ;
        calculatePrecision(setosas.size(), versicolor.size(), virginica.size());
        
    return 0;
}
