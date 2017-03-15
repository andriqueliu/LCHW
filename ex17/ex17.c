/*
Stack vs. Heap

So for practical purposes, malloc == heap, else == stack.
This isn't a perfect representation, but it'll do for now.

If you need something to stick around for a long time, a big chunk of data,
etc., go heap.
Else, if you need something around only for a little bit and need it really fast,
go stack. 

Lots more details...

Note: design patterns in creation and destruction... Easier to organize to use a create
function that makes everything or not, and then a destroy function that frees everything

Note: streams found in files

Note: Check for null pointers/etc. by using if (!ptr), etc. Or you could use == NULL, but
NULL evaluates to false anyway.

Note: This program creates a file, from which Databases of user-defined information
(in this case Address structs) can be stored and accessed 
*/

// ??? Arrays passed... by value? by reference?

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

// An Address holds data about someone:
// Location in the Database, whether their profile is "set," their name,
// and their email address. 
struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

// A Database holds an array of fixed length of Addresses.
struct Database {
	struct Address rows[MAX_ROWS];
};

// A Connection holds information about a file and its corresponding Database.
struct Connection {
	FILE *file;
	struct Database *db;
};

// die is used to kill the program if there is anything wrong
void die(const char *message)
{
	// When you have an error return from a function, it will usually set an external var.
	// errno. Here, you see if errno is set, and perror the error message if it is set.
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1); // Exit the program
}

// Address_print prints out an Address entry's id, name, and email address.
// Inputs:
// struct Address pointer, used to access struct's information
void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

// Database_load loads a Database.
// Inputs:
// struct Connection pointer, used to refer to a Connection's linked file and Database.
void Database_load(struct Connection *conn)
{
	// fread reads (3) items of data, each of size (2), from the stream pointed to by (4),
	// and stores them into the location given by (1). This function allows us to access
	// changes made to files, which we can access out of runtime (because of Database_write).
	//
	// fread returns the number of items written to or read from
	// 
	// rc is just used for error checking
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) {
		die("Failed to load database.");
	}
}

// Database_open creates a new Connection to a new Database, and also checks for errors
// in this process.
// This function allows the user to define their desired mode: 
// c: Create a file
// else: Can read from or write to a file
// Inputs:
// const char pointer filename, used to select file by name
// char mode, used to select which mode of operation
// Returns a pointer to a Connection
struct Connection *Database_open(const char *filename, char mode)
{
	// Create Connection pointer, points to a new Connection
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) {
		die("Memory error.");
	}

	// conn's db will point to a new Database
	conn->db = malloc(sizeof(struct Database));
	if (!conn->db) {
		die("Memory error.");
	}

	if (mode == 'c') {
		conn->file = fopen(filename, "w");  // w: writing
	} else {
		conn->file = fopen(filename, "r+"); // r+: Reading and Writing

		// Is this step really necessary? Look below... 
		if (conn->file) {
			Database_load(conn);
		}
	}

	if (!conn->file) {
		die("Failed to open the file.");
	}

	return conn;
}

// Database_close will close the Database pointed to by conn.
// Note: Anything that has had memory allocated for it will need to be freed!!!
// ??? Reverse the order of freeing? Break?
void Database_close(struct Connection *conn)
{
	if (conn) {
		// These if statements: best practice... just in case for instance one part is missing,
		// doesn't throw an error right away, etc.
		if (conn->file) {
			fclose(conn->file); // Flushes the stream, and also closes the underlying file
		}
		if (conn->db) {
			free(conn->db);     // Free database
		}
		free(conn);             // Free the connection
	}
}

// Database_write writes to the file from the Database. This function effectively allows 
// us to write to a file and refer back to our changes later.
// Inputs:
// struct Connection pointer, used to refer to the Database
void Database_write(struct Connection *conn)
{
	// rewind sets the file position indicator for the stream pointed to by (1) to the
	// beginning of the file.
	rewind(conn->file);

	// fwrite writes to the stream specified by (4) from the location in memory specified
	// by (1). (2) and (3) are the same as fread.
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) {
		die("Failed to write address");
	}

	// fflush flushes the stream
	rc = fflush(conn->file);
	if (rc == -1) {
		die("Cannot flush database");
	}
}

// Database_create creates a Database, initializing Addresses
void Database_create(struct Connection *conn)
{
	int i = 0;

	for (i = 0; i < MAX_ROWS; i++) {
		// Make a prototype to initialize it
		struct Address addr = { .id = i, .set = 0 };
		// Then just assign it
		conn->db->rows[i] = addr; // You can set structs to each other == copying
	}
}

// Database_set sets the Address in the Database found in conn, using the position id,
// name, and email address.
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	// Syntax: address of (conn... db... rows... position in the array)
	struct Address *addr = &conn->db->rows[id];
	if (addr->set) {
		die("Already set, delete it first.");
	}

	addr->set = 1;
	// WARNING: bug, read the "How to break it" and fix this
	char *res = strncpy(addr->name, name, MAX_DATA);
	// Demonstrate the strncpy bug
	if (!res) {
		die("Email copy failed.");
	}

	res = strncpy(addr->email, email, MAX_DATA);
	if (!res) {
		die("Email copy failed");
	}
}

// Database_get prints out an Address's details using its position id in the Database
// found using conn.
void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if (addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set");
	}
}

// Database_delete reinitializes/resets an Address in its Database.
void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = { .id = id, .set = 0 };
	conn->db->rows[id] = addr; // Again, assigning a struct to a struct
}

// Database_list lists the set Addresses in a Database found in conn.
void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for (i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if (cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		die("USAGE: ex17 <dbfile> <action> [action params]");
	}

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if (argc > 3) {
		id = atoi(argv[3]);
	}
	if (id >= MAX_ROWS) {
		die("There aren't that many records");
	}

	// Choose what to do based on action
	switch (action) {
		// Create a database
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;
		// Get information (about one id)
		case 'g':
			if (argc != 4) {
				die("Need an id to get");
			}

			Database_get(conn, id);
			break;
		// Set an id
		case 's':
			if (argc != 6) {
				die("Need id, name, email to set");
			}

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		// Delete an id
		case 'd':
			if (argc != 4) {
				die("Need id to delete");
			}

			Database_delete(conn, id);
			Database_write(conn);
			break;
		// List all ids
		case 'l':
			Database_list(conn);
			break;
		// !!! Removing default is fine, syntax wise.
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}
