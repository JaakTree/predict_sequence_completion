all: knn clean

knn: main.o Metrics.o Filtering.o Reader.o Separation.o KNearestNeighbours.o ExceptionHandler.o InputDataUnit.o InputParametersValidator.o KNearestNeighboursController.o Writer.o
	g++ --std=c++11 -O3 main.o Metrics.o Filtering.o Reader.o Separation.o KNearestNeighbours.o ExceptionHandler.o InputDataUnit.o InputParametersValidator.o KNearestNeighboursController.o Writer.o -o knn

main.o: main.cpp
	g++ -c --std=c++11 -O3 main.cpp

Metrics.o: Metrics.cpp
	g++ -c --std=c++11 -O3 Metrics.cpp

Filtering.o: Filtering.cpp
	g++ -c --std=c++11 -O3 Filtering.cpp

Reader.o: Reader.cpp
	g++ -c --std=c++11 -O3 Reader.cpp

Separation.o: Separation.cpp
	g++ -c --std=c++11 -O3 Separation.cpp

KNearestNeighbours.o: KNearestNeighbours.cpp
	g++ -c --std=c++11 -O3 KNearestNeighbours.cpp

ExceptionHandler.o: ExceptionHandler.cpp
	g++ -c --std=c++11 -O3 ExceptionHandler.cpp

InputDataUnit.o: InputDataUnit.cpp
	g++ -c --std=c++11 -O3 InputDataUnit.cpp

InputParametersValidator.o: InputParametersValidator.cpp
	g++ -c --std=c++11 -O3 InputParametersValidator.cpp

KNearestNeighboursController.o: KNearestNeighboursController.cpp
	g++ -c --std=c++11 -O3 KNearestNeighboursController.cpp

Writer.o: Writer.cpp
	g++ -c --std=c++11 -O3 Writer.cpp

clean:
	-rm -f *o
