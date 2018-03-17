#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
   double x, y;
   Point() {}
   Point(double x_, double y_) : x(x_), y(y_) {}
};

struct Edge {
	int vertex[2];
	Edge() {}
	Edge(int v0, int v1) { vertex[0] = v0; vertex[1] = v1; }
};

struct Triangle
{
   int vertex[3];
   Triangle() {}
   Triangle(int v0, int v1, int v2) { vertex[0] = v0; vertex[1] = v1; vertex[2] = v2; }
};

void setupProblem(vector<Point>& vertices, vector<Triangle>& faces) {
   vertices.resize(6);
   vertices[0] = Point(-1., 0.);
   vertices[1] = Point( 0., 0.);
   vertices[2] = Point( 0., 0.001);
   vertices[3] = Point( 1., 0.);
   vertices[4] = Point( 0.,-1.);
   vertices[5] = Point( 0., 1.);

   faces.resize(6);
   faces[0] = Triangle(0,1,2);
   faces[1] = Triangle(1,2,3);
   faces[2] = Triangle(2,3,5);
   faces[3] = Triangle(0,2,5);
   faces[4] = Triangle(0,1,4);
   faces[5] = Triangle(1,3,4);
}

vector<Edge> countEdges(vector<Point>& vertices);
vector<Edge> findSmall(vector<Point>& vertices, vector<Edge>& edges);
vector<Triangle> findFaces(vector<Triangle>& faces, vector<Edge>& small);


int main() {

	vector<Point> vertices;
	vector<Triangle> faces;

	setupProblem(vertices, faces);

	vector<Edge> edges = countEdges(vertices);
	vector<Edge> small = findSmall(vertices, edges);
	vector<Triangle> little = findFaces(faces, small);

	cout << "EDGES:\n" << endl;

	for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
		cout << "\t\t" << it->vertex[0] << " " << it->vertex[1] << "\n" << endl;
	}

	cout << "EDGES SMALLER THAN 0.01:\n" << endl;

	for (vector<Edge>::iterator it = small.begin(); it != small.end(); ++it) {
		cout << "\t\t" << it->vertex[0] << " " << it->vertex[1] << "\n" << endl;
	}

	cout << "TRIANGLES WITH SMALL EDGE:\n" << endl;

	for (vector<Triangle>::iterator it = little.begin(); it != little.end(); ++it) {
		cout << "\t\t" << it->vertex[0] << " " << it->vertex[1] << " " << it->vertex[2] << "\n" << endl;
	}

	system("PAUSE");
	return 0;
}




vector<Edge> countEdges(vector<Point>& vertices) {

	vector<Edge> edges;
	vector<Edge> noduplicate;

	double min_up = 100.;
	double min_down = 100.;
	double min_left = 100.;
	double min_right = 100.;

	int i_up = 0;
	int i_down = 0;
	int i_left = 0;
	int i_right = 0;
	int j_up = 0;
	int j_down = 0;
	int j_left = 0;
	int j_right = 0;

	int x = 0;
	int y = 0;

	for( int i=0; i < 5 ; i++) {
		for( int j=0; j < 6; j++) {
				if((vertices[i].x != vertices[j].x) || (vertices[i].y != vertices[j].y)) {

							if((vertices[i].y == vertices[j].y)) {

											if((vertices[j].x > vertices[i].x)) {
					
														if(vertices[j].x - vertices[i].x < min_right) {
						
														min_right = vertices[j].x - vertices[i].x;

														i_right = i;

														j_right = j;

														}
											}

											else {
							 
														if (vertices[i].x - vertices[j].x < min_left) {
						
														min_left = vertices[i].x - vertices[j].x;

														i_left = i;

														j_left = j;

														}

											 }

							}



				

							else if((vertices[i].x == vertices[j].x)) {

											if((vertices[j].y > vertices[i].y)) {
					
														if((vertices[j].y - vertices[i].y) < min_up) {
						
														min_up = vertices[j].y - vertices[i].y;

														i_up = i;

														j_up = j;

														}

											}


											else {

														if(vertices[i].x - vertices[j].x < min_down) {
						
														min_down = vertices[j].y - vertices[i].y;

														i_down = i;

														j_down = j;

														 }
											}

							}

				else edges.push_back(Edge(i,j));
			} 
		}

		if( min_right != 100 ) {
		edges.push_back(Edge(i_right,j_right));
		min_right = 100;
		}

		if( min_left != 100 ) {
		edges.push_back(Edge(i_left,j_left));
		min_left = 100;
		}

		if( min_up != 100 ) {
		edges.push_back(Edge(i_up,j_up));
						min_up = 100;
		}

		if( min_down != 100 ) {
		edges.push_back(Edge(i_down,j_down));
		min_down = 100;
		}

			
			
			
	}

	for (int i=0; i < edges.size(); i++) {

		noduplicate.push_back(Edge(edges[i].vertex[0], edges[i].vertex[1]));
	
		for (int j=0; j < edges.size(); j++) {

			if(( edges[i].vertex[0] == edges[j].vertex[1] ) && (edges[i].vertex[1] == edges[j].vertex[0]))
			{

				if ( edges[i].vertex[0] > edges[j].vertex[0] )
				
				{ noduplicate.pop_back();

				continue;

				}

				continue;
			
			
			}


		}
	}


	
	
	return noduplicate;
}


vector<Edge> findSmall(vector<Point>& vertices, vector<Edge>& edges) {

	vector<Edge> small;


	for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
		if (		pow(pow(abs((vertices[it->vertex[0]].x)-(vertices[it->vertex[1]].x)),2) + pow(abs((vertices[it->vertex[0]].y)-(vertices[it->vertex[1]].y)),2), 0.5)		<		0.01 )

			small.push_back(Edge(it->vertex[0],it->vertex[1]));
	}

	return small;



}

vector<Triangle> findFaces(vector<Triangle>& faces, vector<Edge>& small) {
	
	vector<Triangle> little;

	for (vector<Edge>::iterator it = small.begin(); it != small.end(); ++it) {

		for( int j = 0; j < 6; j++){

			if (( faces[j].vertex[0] == it->vertex[0] ) && ( faces[j].vertex[1] == it->vertex[1] )) { 
				little.push_back(Triangle(faces[j].vertex[0], faces[j].vertex[1], faces[j].vertex[2]));
				continue;
			}

			if (( faces[j].vertex[1] == it->vertex[0] ) && ( faces[j].vertex[2] == it->vertex[1] )) { 
				little.push_back(Triangle(faces[j].vertex[0], faces[j].vertex[1], faces[j].vertex[2]));
				continue;
			}

			if (( faces[j].vertex[0] == it->vertex[0] ) && ( faces[j].vertex[2] == it->vertex[1] )) { 
				little.push_back(Triangle(faces[j].vertex[0], faces[j].vertex[1], faces[j].vertex[2]));
				continue;
			}
		
		
			
		}
	}
	

	return little;

}