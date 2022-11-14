#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define MAX_NAME_LENGTH = 30;

const int NUMBER_OF_ROOMS = 300;
const int MIN_RESERVATION_NUMBER = 10000;
const int MAX_RESERVATION_NUMBER = 99999;
const double SINGLE_ROOM_COST = 100;
const double DOUBLE_ROOM_COST = 150;
const string SINGLE_ROOM_LABEL = "Single";
const string DOUBLE_ROOM_LABEL = "Double";

/// <summary>
/// This enum is used to determine the action which the user wants to perform.
/// </summary>
enum Action {
	ShowRooms = 1,
	Book = 2,
	ShowBookings = 3,
	SearchBooking = 4,
	Exit = 5,
};

/// <summary>
/// This enum is used to determine the type of a room and how much it will cost.
/// </summary>
enum RoomType {
	Single,
	Double
};

/// <summary>
/// This struct is used to store information of a room.
/// </summary>
struct Room {
	int number;
	bool available;
	RoomType roomType;
};

/// <summary>
/// This struct is used to determine the information of a booking.
/// </summary>
struct Booking {
	int reservationNumber;
	string booker_name;
	double cost;
	double discount;
	int number_of_nights;
	vector<Room> rooms;
};

/// <summary>
/// This method prints a welcome message when the application starts.
/// </summary>
void printWelcome() {
	cout << "Welcome to my Hotel Booking Program!" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++" << endl << endl;
}

/// <summary>
/// This method prints all the available actions to the user in the console.
/// </summary>
void printActions() {
	cout << "1: Show Rooms" << endl;
	cout << "2: Add Booking" << endl;
	cout << "3: View Bookings" << endl;
	cout << "4: Search Bookings" << endl;
	cout << "5: Quit" << endl << endl;
	cout << "Select your action: ";
}

/// <summary>
/// This method reads the entire line when a user is entering information to the console.
/// </summary>
/// <returns>
/// The return value is the entered line from the user.
/// </returns>
string readLineInput() {
	string input;
	cin.ignore();
	getline(cin, input);
	return input;
}

/// <summary>
/// This method reads a number input from the user. It checks if the given input is a valid number. If not it will ask the user again for a valid number.
/// </summary>
/// <returns>
/// The return value is the number value from the user
/// </returns>
int readNumberInput() {
	int input = -1;
	bool valid = false;
	do
	{
		cin >> input;
		if (cin.good())
		{
			valid = true;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input; Please enter a numeric value: ";
		}
	} while (!valid);
	return input;
}

/// <summary>
/// This method validates if the number input is in a certain range. If its not the case it will ask the user to give a number value in the certain range.
/// </summary>
/// <param name="min">The min value which the return value can have</param>
/// <param name="max">The max value which the return value can have</param>
/// <returns>
/// The return value is the number value from the user
/// </returns>
int readValidatedNumber(int min, int max) {
	int number;
	bool isValid = false;
	while (!isValid)
	{
		number = readNumberInput();
		if (number < min || number > max) {
			cout << "The inserted value is not in the range " << min << "-" << max << endl;
			cout << "Please insert a valid numeric value: ";
		}
		else {
			isValid = true;
		}
	}
	return number;
}

/// <summary>
/// This method determines if the room is available for a booking.
/// </summary>
/// <param name="rooms">All the existing rooms</param>
/// <param name="roomNumber">The room number to test</param>
/// <returns>The return value is the availability of the room</returns>
bool isRoomAvailable(Room* rooms, int roomNumber) {
	return rooms[roomNumber - 1].available;
}

/// <summary>
/// This method returns the cost of the room depending on its RoomType
/// </summary>
/// <param name="room">The room to check</param>
/// <returns>
/// The cost of the room
/// </returns>
double getRoomCost(Room room) {
	double cost = 0;
	switch (room.roomType) {
	case Single: cost = SINGLE_ROOM_COST;
		break;
	case Double: cost = DOUBLE_ROOM_COST;
		break;
	}
	return cost;
}

/// <summary>
/// This method returns the string value of the room type.
/// </summary>
/// <param name="room">The room</param>
/// <returns>The return value is the label of the room type</returns>
string getRoomType(Room room) {
	string roomType;
	switch (room.roomType) {
	case Single: roomType = SINGLE_ROOM_LABEL;
		break;
	case Double: roomType = DOUBLE_ROOM_LABEL;
		break;
	}
	return roomType;
}

/// <summary>
/// This method displays all the room with its information.
/// </summary>
/// <param name="rooms">All the rooms</param>
void showRooms(Room* rooms) {
	cout << "Rooms:" << endl;
	cout << "------------------------------------------" << endl;
	cout << left << setw(10) << "Type" << left << setw(10) << "Room Nr." << left << setw(10) << "Cost" << left << setw(10) << "Available" << endl;
	cout << "------------------------------------------" << endl;

	for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
		cout << left << setw(10) << getRoomType(rooms[i]) << left << setw(10) << rooms[i].number << left << setw(10) << getRoomCost(rooms[i]) << left << setw(10) << (rooms[i].available ? "yes" : "no") << endl;
	}
	cout << endl;
}

/// <summary>
/// This method shows a certain booking with its information.
/// </summary>
/// <param name="booking">The booking which should be shown</param>
void showBooking(Booking booking) {

	cout << "Booking " << booking.reservationNumber << ":" << endl;
	cout << "-----------------------------" << endl;
	cout << "Reserved for: " << booking.booker_name << endl;
	cout << "Number of nights: " << booking.number_of_nights << endl;
	cout << "Discount: " << booking.discount*100 << "%" << endl;
	cout << "Total cost: " << booking.cost << endl;
	cout << "Rooms:" << endl;
	for (int j = 0; j < booking.rooms.size(); j++) {
		cout << getRoomType(booking.rooms[j]) << " Room: " << booking.rooms[j].number << " Cost: "  << getRoomCost(booking.rooms[j]) << endl;
	}
	cout << endl;
}

/// <summary>
/// This method shows all the existing bookings
/// </summary>
/// <param name="bookings">All the existing bookings</param>
void showBookings(vector<Booking> bookings) {
	for (int i = 0; i < bookings.size(); i++) {
		showBooking(bookings[i]);
	}
}

/// <summary>
/// This method is used to read the user input and search for bookings.
/// </summary>
/// <param name="bookings">All the bookings</param>
void searchBooking(vector<Booking> bookings) {
	cout << endl;
	cout << "Enter the booking you are looking for: ";
	string searchRequest = readLineInput();
	for (int i = 0; i < bookings.size(); i++) {
		if (bookings[i].booker_name == searchRequest || to_string(bookings[i].reservationNumber) == searchRequest) {
			cout << endl;
			showBooking(bookings[i]);
		}
	}
	cout << endl << endl;
}

/// <summary>
/// This method is used to get a random discount for the reservations.
/// </summary>
/// <returns>The return value is the discount</returns>
double getRandomDiscount() {
	double discount = 0;
	switch (rand() % 3) {
		case 1: discount = 0;
			break;
		case 2: discount = 0.1;
			break;
		case 3: discount = 0.2;
			break;
	}
	return discount;
}

/// <summary>
/// This method is used to calculate the total cost for the passed booking and adds a discount to it.
/// </summary>
/// <param name="booking">the booking to calculate the total cost</param>
/// <returns>The return value is the tocal cost of the booking</returns>
double calculateCost(Booking booking) {
	double cost = 0;
	for (int i = 0; i < booking.rooms.size(); i++) {
		cost += getRoomCost(booking.rooms[i]) * booking.number_of_nights;
	}
	return cost * (1-booking.discount);
}

/// <summary>
/// This method is used to ask the user for the booking information and adds the booking to the system.
/// </summary>
/// <param name="bookings">The existing bookings</param>
/// <param name="rooms">All the existing rooms</param>
void bookRoom(vector<Booking> &bookings, Room rooms[]) {
	Booking booking;

	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, booking.booker_name);
	cout << "Enter how many rooms you want to book: ";
	int amountOfRooms = readValidatedNumber(1, NUMBER_OF_ROOMS);
	cout << "Enter which room you want to book." << endl;
	for (int i = 0; i < amountOfRooms; i++) {
		cout << "Room Number " << i + 1 << ": ";
		bool roomCanBeBooked = false;
		int roomNumber;
		while (!roomCanBeBooked) {
			roomNumber = readValidatedNumber(1, NUMBER_OF_ROOMS);
			roomCanBeBooked = isRoomAvailable(rooms, roomNumber);
			if (!roomCanBeBooked) {
				cout << "The room " << roomNumber << " is not available." << endl;
				cout << "Please choose another room: ";
			}
		}
		rooms[roomNumber - 1].available = false;
		booking.rooms.insert(booking.rooms.end(), 1, rooms[roomNumber-1]);
	}

	cout << "Enter the amount of nights you want to book the rooms: ";
	booking.number_of_nights = readValidatedNumber(1, INT_MAX);
	bool isReservationNumberValid = true;
	int reservationNumber;
	do {
		reservationNumber = rand() % 99999 + 10000;
		for (int i = 0; i < bookings.size(); i++) {
			if (bookings[i].reservationNumber == reservationNumber) {
				isReservationNumberValid = false;
			}
		}
	} while (!isReservationNumberValid);
	booking.reservationNumber = reservationNumber;
	booking.discount = getRandomDiscount();
	booking.cost = calculateCost(booking);
	bookings.insert(bookings.end(), 1, booking);
	cout << endl;
}

/// <summary>
/// This method is used to initialize the rooms with its number and the type of the room.
/// </summary>
/// <param name="rooms">The array where the rooms should be filled in</param>
void initializeRooms(Room rooms[]) {
	for (int i = 1; i <= NUMBER_OF_ROOMS; i++) {
		Room room;
		room.number = i;
		if (NUMBER_OF_ROOMS / 2 > i) {
			room.roomType = Single;
		}
		else {
			room.roomType = Double;
		}
		rooms[i - 1] = room;
	}
}

/// <summary>
/// This method is the main method of the application. It initializes the arrays and asks the user for its desired actions.
/// </summary>
int main()
{
	bool isRunning = true;
	Room rooms[NUMBER_OF_ROOMS];
	vector<Booking> bookings;
	initializeRooms(rooms);
	printWelcome();
	while (isRunning) {
		printActions();
		int action = readNumberInput();
		cout << endl;
		switch (action) {
			case Book: 
				bookRoom(bookings, rooms);
				showBooking(bookings[bookings.size()-1]);
				break;

			case ShowRooms: showRooms(rooms);  break;
			case ShowBookings: showBookings(bookings);  break;
			case SearchBooking: searchBooking(bookings);  break;
			case Exit: isRunning = false;  break;
			default: cout << "This action does not exist! Please choose an existing Aciton." << endl; break;
		}
	}
	return 0;
}
