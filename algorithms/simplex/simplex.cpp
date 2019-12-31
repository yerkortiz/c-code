#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Simplex{

    private:
        int rows, cols;

        std::vector <std::vector<float> > A;

        std::vector<float> B;

        std::vector<float> C;

        float maximum;

        bool isUnbounded;

    public:
        Simplex(std::vector <std::vector<float> > matrix,std::vector<float> b ,std::vector<float> c){
            maximum = 0;
            isUnbounded = false;
            rows = matrix.size();
            cols = matrix[0].size();
            A.resize( rows , vector<float>( cols , 0 ) );
            B.resize(b.size());
            C.resize(c.size());

            for(int i= 0;i<rows;i++){           
                for(int j= 0; j< cols;j++ ){
                    A[i][j] = matrix[i][j];
                }
            }

            for(int i=0; i< c.size() ;i++ ){     
                C[i] = c[i] ;
            }
            for(int i=0; i< b.size();i++ ){      
                B[i] = b[i];
            }




        }

        bool simplexAlgorithmCalculataion(){
            if(checkOptimality()==true){
			    return true;
            }

            int pivotColumn = findPivotColumn();


            if(isUnbounded == true){
                cout<<"Error unbounded"<<endl;
			    return true;
            }

            int pivotRow = findPivotRow(pivotColumn);

            doPivotting(pivotRow,pivotColumn);

            return false;
        }

        bool checkOptimality(){
            
            bool isOptimal = false;
            int positveValueCount = 0;

            
            for(int i=0; i<C.size();i++){
                float value = C[i];
                if(value >= 0){
                    positveValueCount++;
                }
            }
            
            if(positveValueCount == C.size()){
                isOptimal = true;
                print();
            }
            return isOptimal;
        }

        void doPivotting(int pivotRow, int pivotColumn){

            float pivetValue = A[pivotRow][pivotColumn];

            float pivotRowVals[cols];

            float pivotColVals[rows];

            float rowNew[cols];

            maximum = maximum - (C[pivotColumn]*(B[pivotRow]/pivetValue));  
             
            for(int i=0;i<cols;i++){
                pivotRowVals[i] = A[pivotRow][i];
             }
             
            for(int j=0;j<rows;j++){
                pivotColVals[j] = A[j][pivotColumn];
            }

            
             for(int k=0;k<cols;k++){
                rowNew[k] = pivotRowVals[k]/pivetValue;
             }

            B[pivotRow] = B[pivotRow]/pivetValue;


             
            for(int m=0;m<rows;m++){
            
                if(m !=pivotRow){
                    for(int p=0;p<cols;p++){
                        float multiplyValue = pivotColVals[m];
                        A[m][p] = A[m][p] - (multiplyValue*rowNew[p]);
                    }

                }
             }

            for(int i=0;i<B.size();i++){
                if(i != pivotRow){

                        float multiplyValue = pivotColVals[i];
                        B[i] = B[i] - (multiplyValue*B[pivotRow]);

                }
            }
                float multiplyValue = C[pivotColumn];
                 for(int i=0;i<C.size();i++){
                    C[i] = C[i] - (multiplyValue*rowNew[i]);

                }


             for(int i=0;i<cols;i++){
                A[pivotRow][i] = rowNew[i];
             }


        }
        void print(){
            for(int i=0; i<rows;i++){
                for(int j=0;j<cols;j++){
                    cout<<A[i][j] <<" ";
                }
                cout<<""<<endl;
            }
            cout<<""<<endl;
        }

        int findPivotColumn(){

            int location = 0;
            float minm = C[0];



            for(int i=1;i<C.size();i++){
                if(C[i]<minm){
                    minm = C[i];
                    location = i;
                }
            }

            return location;

        }
        int findPivotRow(int pivotColumn){
            float positiveValues[rows];
            std::vector<float> result(rows,0);
            int negativeValueCount = 0;
            for(int i=0;i<rows;i++){
                if(A[i][pivotColumn]>0){
                    positiveValues[i] = A[i][pivotColumn];
                }
                else{
                    positiveValues[i]=0;
                    negativeValueCount+=1;
                }
            }
            if(negativeValueCount==rows){
                isUnbounded = true;
            }
            else{
                for(int i=0;i<rows;i++){
                    float value = positiveValues[i];
                    if(value>0){
                        result[i] = B[i]/value;

                    }
                    else{
                        result[i] = 0;
                    }
                }
            }
            float minimum = 99999999;
            int location = 0;
            for(int i=0;i<sizeof(result)/sizeof(result[0]);i++){
                if(result[i]>0){
                    if(result[i]<minimum){
                        minimum = result[i];

                        location = i;
                    }
                }

            }

            return location;

        }

        void CalculateSimplex(){
            bool end = false;


            while(!end) {
                bool result = simplexAlgorithmCalculataion();
                if( result==true ){
                    end = true;
                }
            }
            cout<<"Variables"<<endl;
            for(int i=0;i< A.size(); i++){  
                int count0 = 0;
                int index = 0;
                for(int j=0; j< rows; j++){
                    if(A[j][i]==0.0){
                        count0 += 1;
                    }
                    else if(A[j][i]==1){
                        index = j;
                    }
                }

                if(count0 == rows -1 ){

                    cout<<"variable"<<index+1<<": "<<B[index]<<endl;  
                }
                else{
                    cout<<"variable"<<index+1<<": "<<0<<endl;

                }

            }


           cout<<""<<endl;
           cout<<"Valor Maximo: "<<maximum<<endl;  




        }

};

int main()
{
    int colSizeA=6; 
    int rowSizeA = 3;  

    float C[]= {-3, -4, -2, 0, 0, 0};  
    float B[]={1100, 600, 400};  
    float a[3][6] = {   
                   { 1,  2,  0, 1, 0, 0},
                   { 2,  0,  2, 0, -1, 0},
                   { 4,  3,  1, 0, 0, 1}
             };

    std::vector <std::vector<float> > vec2D(rowSizeA, std::vector<float>(colSizeA, 0));
    std::vector<float> b(rowSizeA,0);
    std::vector<float> c(colSizeA,0);
    for(int i=0;i<rowSizeA;i++){        
            for(int j=0; j<colSizeA;j++){
                vec2D[i][j] = a[i][j];
            }
       }
    for(int i=0;i<rowSizeA;i++){
            b[i] = B[i];
       }
    for(int i=0;i<colSizeA;i++){
            c[i] = C[i];
       }
      Simplex simplex(vec2D,b,c);
      simplex.CalculateSimplex();


    return 0;
}