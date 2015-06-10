default: Vehicle.cpp DiscoverVehicle.cpp RescueVehicle.cpp AnalyseVehicle.cpp Ground.cpp World.cpp Simulation.cpp Main.cpp
	g++ -o simulation Vehicle.cpp DiscoverVehicle.cpp RescueVehicle.cpp AnalyseVehicle.cpp Ground.cpp Main.cpp World.cpp Simulation.cpp

clean:
	rm -f simulation