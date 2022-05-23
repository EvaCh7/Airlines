/***************************************************
 *                                                 *
 * file: twitter.c                                 *
 *                                                 *
 * @Author  Iacovos G. Kolokasis                   *
 * @Version 25-02-2020                             *
 * @email   kolokasis@csd.uoc.gr                   *
 *                                                 *
 * @brief   Implementation of airlines.h            *
 *                                                 *
 ***************************************************
 */

#include "airlines.h"


_airlines_l * create_airlinenode(int aId);
_airplane * create_airplanenode(int pId, int dest, int depart_time);
_flights_l * create_flightnode(int pId, int depart_time);
_flights_l * create_sentinelnode();

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
	int i = 0;

	for (i = 0; i < MAX_DEST;i++) {
		destTable[i].sentinel_p = create_sentinelnode;
		destTable[i].flight_p = destTable[i].sentinel_p;
	}

    return 1;
}

/**
 * @brief Register airline
 *
 * @param aId The airline's id
 *
 * @return 1 on success
 *         0 on failure
 */


int register_airline(int aId) {
	_airlines_l *ptr = airlines_p;
	_airlines_l *new = create_airlinenode(aId);

	if (new == NULL) return 0;

	if (airlines_p == NULL) {
		airlines_p = new;
		new->next = new->prev = airlines_p;
		printf("\tAirlines: %d\n", airlines_p->aId);

		return 1;
	}

	while (ptr->next != airlines_p) {
		if (ptr->aId == aId) return 0;
		ptr = ptr->next;
	}
	
	airlines_p->prev = ptr;
	ptr = airlines_p->prev;
	ptr->next = new;
	new->prev = ptr;
	new->next = airlines_p;
	airlines_p->prev = new;

	ptr = airlines_p;
	printf("Airlines: <%d>", airlines_p->aId);
	ptr = ptr->next;

	while (ptr != airlines_p) {
			printf(",<%d>", ptr->aId);
			ptr = ptr->next;
	}
	printf("\n");

	return 1;
}

_airlines_l * create_airlinenode(int aId) {
	_airlines_l *new = (_airlines_l*)malloc(sizeof(_airlines_l));
	new->aId = aId;
	new->next = NULL;
	new->prev = NULL;
	new->p_root = NULL;

	return new;
}


/**
 * @brief Insert new airplane to the list of the certain airline with aId
 *
 * @param aId         The airlines id
 * @param pId         The airplanes id
 * @param dest        Destination Id [0-9]
 * @param depart_time Departure time
 *
 * @return 1 on success
 *         0 on failure
 */

int insert_airplanes(int aId, int pId, int dest, int depart_time) {
	_airlines_l *ptr1 = airlines_p;
	_airplane *ptr2 = NULL;
	_airplane *new = create_airplanenode(pId, dest, depart_time);
	_flights_l *head = destTable[dest].flight_p;
	_flights_l *new1 = create_flightnode(pId, depart_time);
	_flights_l *ptr3 = NULL;
	_flights_l *sentinel = create_sentinelnode();
	int i = 1;
	

	while (ptr1->aId != aId) {
		if (ptr1->next == airlines_p && ptr1->aId != aId) return 0;
		else {
			ptr1 = ptr1->next;
		}
	}
	
	ptr2 = ptr1->p_root;

	if (ptr2 == NULL || ptr2->pId > new->pId) {
		new->next = ptr2;
		ptr1->p_root = new;
	}
	else {
		while (ptr2->next != NULL && ptr2->next->pId < new->pId) {
			ptr2 = ptr2->next;
		}

		new->next = ptr2->next;
		ptr2->next = new;
	}


	ptr3 = destTable[dest].flight_p;

	
	if (destTable[dest].flight_p == destTable[dest].sentinel_p) {
		new1->next = destTable[dest].sentinel_p;
		destTable[dest].flight_p = new1;
		/*destTable[dest].sentinel_p->next = new1;
		destTable[dest].sentinel_p->depart_time = new1->depart_time;
		destTable[dest].sentinel_p->pId = new1->pId;
	*/}
	else if(destTable[dest].flight_p->depart_time > new1->depart_time){
		new1->next = destTable[dest].flight_p;
		destTable[dest].flight_p = new1;
		/*destTable[dest].sentinel_p->next = new1;
		destTable[dest].sentinel_p->depart_time = new1->depart_time;
		destTable[dest].sentinel_p->pId = new1->pId;
	*/}
	else {
		/*if (destTable[dest].sentinel_p->depart_time < depart_time) ptr3 = destTable[dest].sentinel_p->next;
		*/while (ptr3->next != destTable[dest].sentinel_p && ptr3->next->depart_time < new1->depart_time) {
				ptr3 = ptr3->next;
		}
		if (ptr3->next == destTable[dest].sentinel_p) {
			new1->next = destTable[dest].sentinel_p;
			ptr3->next = new1;

		}
		else {
			new1->next = ptr3->next;
			ptr3->next = new1;
		}
/*		destTable[dest].sentinel_p->next = new1;
		destTable[dest].sentinel_p->pId = new1->pId;
		destTable[dest].sentinel_p->depart_time = new1->depart_time;
	*/}



	ptr1 = airlines_p;
	ptr2 = airlines_p->p_root;
	printf("Airline%d=", i);
	while (ptr2 != NULL) {
		printf("<%d:%d> ", ptr2->pId, airlines_p->aId);
		ptr2 = ptr2->next;
	}
	printf("\n");
	ptr1 = ptr1->next;
	i++;

	while (ptr1 != airlines_p) {
		ptr2 = ptr1->p_root;
		printf("Airline%d=", i);
		while (ptr2 != NULL) {
			printf("<%d:%d> ", ptr2->pId, ptr1->aId);
			ptr2 = ptr2->next;
		}
		printf("\n");
		ptr1 = ptr1->next;
		i++;
	}
	
	return 1;
}
/*
		if (ptr3 == destTable[dest].flight_p && ptr3->depart_time == new1->depart_time && ptr3->pId > new1->pId) {
			printf("SUP");
			new1 = destTable[dest].flight_p;
			new1->next = ptr3;
		}
		else if (ptr3->depart_time == new1->depart_time && ptr3->pId > new1->pId) {
			printf("First");
			new1->next = ptr3->next;
			ptr3->next = new1;
		}
		else if (ptr3->depart_time == new1->depart_time && ptr3->pId < new1->pId) {
			printf("Second");
			ptr3 = ptr3->next;
			new1 = ptr3->next;
			ptr3->next = new1;
		}
		else */


_airplane * create_airplanenode(int pId, int dest, int depart_time) {
	_airplane *new = (_airplane*)malloc(sizeof(_airplane));
	new->pId = pId;
	new->dest = dest;
	new->depart_time = depart_time;
	new->next = NULL;
	
	return new;
}

/**
 * @brief Cancel flight
 *
 * @param aId         The airlines id
 * @param pId         The airplanes id
 * @param dest        Destination Id [0-9]
 *
 * @return 1 on success
 *         0 on failure
 */
int cancel_flight(int aId, int pId, int dest) {
	_airlines_l *ptr1 = airlines_p;
	_airplane *ptr2;
	_airplane *pre = NULL;
	_flights_l *head = destTable[dest].flight_p;
	_flights_l *ptr3;
	_flights_l *pre3 = NULL;
	_flights_l *sentinel = create_sentinelnode();
	int i = 1;

	while (ptr1->aId != aId) {
		if (ptr1->next == airlines_p && ptr1->aId != aId) return 0;
		else {
			ptr1 = ptr1->next;
		}
	}

	ptr2 = ptr1->p_root;

	if (ptr2 == NULL) return 0;

	if (ptr1->p_root->pId == pId) {
		ptr1->p_root = ptr2->next;
		free(ptr2);
		
		return 1;
	}

	while (ptr2 != NULL && ptr2->pId != pId) {
		pre = ptr2;
		ptr2 = ptr2->next;
	}

	if (ptr2 == NULL) return 0;

	pre->next = ptr2->next;
	free(ptr2);


	sentinel->pId = pId;
	ptr3 = head;
	pre3 = head;

	if (destTable[dest].flight_p->pId == pId) {
		destTable[dest].flight_p = ptr3->next;   
		ptr3 = NULL;
		free(ptr3);
/*		destTable[dest].sentinel_p->depart_time = destTable[dest].flight_p->depart_time;
		destTable[dest].sentinel_p->pId = destTable[dest].flight_p->pId;
		printf("First%d", destTable[dest].sentinel_p->depart_time);
	*/}
	else {
		/*if (destTable[dest].sentinel_p->depart_time < ptr2->depart_time) ptr3 = destTable[dest].sentinel_p->next;
		*/while (ptr3->next != destTable[dest].sentinel_p && ptr3->pId != pId) {
			pre3 = ptr3;
			ptr3 = ptr3->next;
		}
		/*if (ptr3 == destTable[dest].sentinel_p) return 0;
		*/

		pre3->next = ptr3->next;
		ptr3 = ptr3->next;
		pre3 = NULL;
		free(pre3);


/*		destTable[dest].sentinel_p->depart_time = ptr3->depart_time;
	*/	printf("%d", destTable[dest].sentinel_p->depart_time);
	}

	ptr1 = airlines_p;
	ptr2 = airlines_p->p_root;
	printf("\nAirline%d=", i);
	while (ptr2 != NULL) {
		printf("<%d:%d> ", ptr2->pId, airlines_p->aId);
		ptr2 = ptr2->next;
	}
	printf("\n");
	ptr1 = ptr1->next;
	i++;

	while (ptr1 != airlines_p) {
		ptr2 = ptr1->p_root;
		printf("Airline%d=", i);
		while (ptr2 != NULL) {
			printf("<%d:%d> ", ptr2->pId, ptr1->aId);
			ptr2 = ptr2->next;
		}
		printf("\n");
		ptr1 = ptr1->next;
		i++;
	}

	
	ptr3 = destTable[dest].flight_p;

	printf("Flights%d:\n\t", dest);
	while (ptr3 != destTable[dest].sentinel_p) {
		printf("<%d,%d>", ptr3->pId, ptr3->depart_time);
		ptr3 = ptr3->next;
	}
	printf("\n");
	

    return 1;
}

_flights_l * create_flightnode(int pId, int depart_time) {
	_flights_l *new = (_flights_l*)malloc(sizeof(_flights_l));
	new->pId = pId;
	new->depart_time = depart_time;
	new->next = NULL;

	return new;
}


_flights_l * create_sentinelnode() {
	_flights_l *new = (_flights_l*)malloc(sizeof(_flights_l));
	new->pId = -1;
	new->depart_time = NULL;
	new->next = NULL;

	return new;
}

/**
 * @brief Delete airline
 *
 * @param aId         The airlines id
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_airline(int aId) {
	_airlines_l *ptr = airlines_p;
	_airlines_l *pre = NULL;
	_airplane *ptr1;
	_airplane *pre1 = NULL;
	_flights_l *head;
	_flights_l *ptr3;
	_flights_l *pre3 = NULL;
	_flights_l *sentinel = create_sentinelnode();
	int i = 0;
	int z = 1;


	if (airlines_p == NULL) return 0;

	if (airlines_p->aId == aId) {
		ptr1 = ptr->p_root;

		while (ptr1 != NULL) {
			pre1 = ptr1;
			ptr1 = ptr1->next;
			pre1 = NULL;
			free(pre1);
		}

		airlines_p = ptr->next;
		ptr = NULL;
		free(ptr);
		pre->next = airlines_p;
		airlines_p->prev = pre;
	}

	else {
		ptr = ptr->next;
		while (ptr != airlines_p && ptr->aId != aId) {
			pre = ptr;
			ptr = ptr->next;
		}
		if (ptr == airlines_p) return 0;
		ptr1 = ptr->p_root;



		while (ptr1 != NULL) {

			for (i = 0;i < MAX_DEST;i++) {
				head = destTable[ptr1->dest].flight_p;
				ptr3 = destTable[ptr1->dest].flight_p;

				while (ptr3 != destTable[ptr1->dest].sentinel_p && ptr3->pId != ptr1->pId) {
					pre3 = ptr3;
					ptr3 = ptr3->next;
				}
				if (ptr3->pId == head->pId) {
					destTable[ptr1->dest].flight_p = ptr3->next;
					free(ptr3);
				}
				else {
					if (ptr3 == destTable[ptr1->dest].sentinel_p) continue;

					pre3->next = ptr3->next;
					free(ptr3);
				}/*
				//printf("%d", destTable[ptr1->dest].sentinel_p->depart_time);
				if (destTable[ptr1->dest].flight_p->pId == ptr1->pId) {
					pre3 = ptr3;
					ptr3 = ptr3->next;
					destTable[ptr1->dest].flight_p = ptr3;
					pre3 = NULL;
					free(pre3);
//					destTable[ptr1->dest].sentinel_p->depart_time = destTable[ptr1->dest].flight_p->depart_time;
	//				destTable[ptr1->dest].sentinel_p->pId = destTable[ptr1->dest].flight_p->pId;
					printf("First %d", destTable[ptr1->dest].sentinel_p->depart_time);
				}
				else {
					printf("Hola");
//					if (destTable[ptr1->dest].sentinel_p->depart_time < ptr1->depart_time) ptr3 = destTable[ptr1->dest].sentinel_p->next;
					while (ptr3->next!= destTable[ptr1->dest].sentinel_p && ptr3->pId != ptr1->pId) {
						printf(".-.");
						pre3 = ptr3;
						ptr3 = ptr3->next;
					}
				
					if (ptr3 == destTable[ptr1->dest].sentinel_p) continue;

					pre3->next = ptr3->next;
					pre3 = ptr3;
					ptr3 = ptr3->next;
					pre3 = NULL;
					free(pre3);

				//	destTable[ptr1->dest].sentinel_p->depart_time = ptr3->depart_time;
					//destTable[ptr1->dest].sentinel_p->pId = ptr3->pId;
					//printf("%d", destTable[ptr1->dest].sentinel_p->depart_time);
				}*/
			}
			pre1 = ptr1;
			ptr1 = ptr1->next;
			pre1 = NULL;
			free(pre1);
		}


		ptr = ptr->next;
		free(ptr->prev);
		pre->next = ptr;
		ptr->prev = pre;
	}

	

	ptr = airlines_p;
	ptr1 = airlines_p->p_root;
	printf("Airline%d=", z);
	while (ptr1 != NULL) {
		printf("<%d:%d> ", ptr1->pId, airlines_p->aId);
		ptr1 = ptr1->next;
	}
	printf("\n");
	ptr = ptr->next;
	z++;

	while (ptr != airlines_p) {
		ptr1 = ptr->p_root;
		printf("Airline%d=", z);
		while (ptr1 != NULL) {
			printf("<%d:%d> ", ptr1->pId, ptr->aId);
			ptr1 = ptr1->next;
		}
		printf("\n");
		ptr = ptr->next;
		z++;
	}

	

    return 1;
}

/**
 * @brief Acquisition airline
 *
 * @param aId1         The first airline id
 * @param aId2         The second airline id
 *
 * @return 1 on success
 *         0 on failure
 */
int acquisition_airline(int aId1, int aId2) {
	_airlines_l *ptr1 = airlines_p;
	_airlines_l *ptr2 = airlines_p;
	_airlines_l *pre1 = NULL;
	_airplane *p1 = NULL;
	_airplane *p2 = NULL;
	_airplane *pre2 = NULL;
	_airplane *new = NULL;
	int i = 1;

	if (airlines_p->aId == aId1) {
		p1 = ptr1->p_root;
	}
	if (airlines_p->aId == aId2) {
		p2 = ptr2->p_root;
	}
	

	pre1 = ptr1;
	ptr1 = ptr1->next;
	while (ptr1 != airlines_p && ptr1->aId != aId1) {
		pre1 = ptr1;
		ptr1 = ptr1->next;
	}
	if(ptr1->aId==aId1) p1 = ptr1->p_root;


	ptr2 = ptr2->next;
	while (ptr2 != airlines_p && ptr2->aId != aId2) {
		ptr2 = ptr2->next;
	}
	if (ptr2->aId == aId2) p2 = ptr2->p_root;


	while (p1 != NULL) {
		new = create_airplanenode(p1->pId, p1->dest, p1->depart_time);

		printf("meow");
		if (ptr2->p_root == NULL) {
			printf("1st");
			ptr2->p_root = new;
			new->next = NULL;
			p2 = new;
		}
		else if (p1->pId < ptr2->p_root->pId) {
			printf("2nd");
			ptr2->p_root = new;
			new->next = p2;
			pre2 = ptr2->p_root;
		}
		else if (p2->next == NULL && p2->pId < p1->pId) {
			printf("3rd");
			p2->next = new;
			new->next = NULL;
		}
		else {
			while (p1->pId > p2->pId && p2->next!=NULL) {
				pre2 = p2;
				p2 = p2->next;
			}
			new->next = p2;
			pre2->next = new;
			pre2 = pre2->next;
		}

		ptr1->p_root = p1->next;
		p1 = NULL;
		free(p1);

		if (ptr1->p_root == NULL) break;
		else {
			p1 = ptr1->p_root;
		}
	}

	if (ptr1->aId == airlines_p->aId) {
		airlines_p = ptr1->next;
		ptr1 = NULL;
		free(ptr1);
		pre1->next = airlines_p;
		airlines_p->prev = pre1;
	}
	else {
		ptr1 = ptr1->next;
		ptr1->prev = NULL;
		free(ptr1->prev);
		pre1->next = ptr1;
		ptr1->prev = pre1;
	}

	ptr1 = airlines_p;
	p1 = airlines_p->p_root;
	printf("Airline%d=", i);
	while (p1 != NULL) {
		printf("<%d:%d> ", p1->pId, airlines_p->aId);
		p1 = p1->next;
	}
	printf("\n");
	ptr1 = ptr1->next;
	i++;

	while (ptr1 != airlines_p) {
		p1 = ptr1->p_root;
		printf("Airline%d=", i);
		while (p1 != NULL) {
			printf("<%d:%d> ", p1->pId, ptr1->aId);
			p1 = p1->next;
		}
		printf("\n");
		ptr1 = ptr1->next;
		i++;
	}

    return 1;
}

/**
 * @brief Subsidiary company
 *
 * @param aId1         The first airline id
 * @param aId2         The second airline id
 * @param dest         Destination
 *
 * @return 1 on success
 *         0 on failure
 */
int subsidiary_airiline(int aId1, int aId2, int dest){
	_airlines_l *ptr1 = airlines_p;
	_airlines_l *ptr2 = airlines_p;
	_airplane *p1 = NULL;
	_airplane *pre1 = NULL;
	_airplane *p2 = NULL;
	_airplane *pre2 = NULL;
	_airplane *new = NULL;
	int i = 1;

	if (airlines_p->aId == aId1) {
		p1 = ptr1->p_root;
	}
	if (airlines_p->aId == aId2) {
		p2 = ptr2->p_root;
	}

	ptr2 = ptr2->next;
	while (ptr2 != airlines_p && ptr2->aId != aId2) {
		ptr2 = ptr2->next;
	}
	p2 = ptr2->p_root;


	ptr1 = ptr1->next;
	while (ptr1 != airlines_p && ptr1->aId != aId1) {
		ptr1 = ptr1->next;
	}
	p1 = ptr1->p_root;


	while (p1 != NULL) {
		if (p1->dest == dest) {
			new = create_airplanenode(p1->pId, p1->dest, p1->depart_time);

			printf("meow");
			if (ptr2->p_root == NULL) {
				printf("1st");
				ptr2->p_root = new;
				new->next = NULL;
				p2 = new;
			}
			else if (p1->pId < ptr2->p_root->pId) {
				printf("2nd");
				ptr2->p_root = new;
				new->next = p2;
				pre2 = ptr2->p_root;
			}
			else if (p2->next == NULL && p2->pId < p1->pId) {
				printf("3rd");
				p2->next = new;
				new->next = NULL;
			}
			else {
				while (p1->pId > p2->pId && p2->next != NULL) {
					pre2 = p2;
					p2 = p2->next;
				}
				new->next = p2;
				pre2->next = new;
				pre2 = pre2->next;
			}

			if (ptr1->p_root == NULL) {
				break;
			}
			if (p1 == ptr1->p_root) {
				ptr1->p_root = p1->next;
				p1 = NULL;
				free(p1);
			}
			else if (p1->next == NULL) {
				pre1->next = NULL;
				p1 = NULL;
				free(p1);
			}
			else {
				pre1->next = p1->next;
				pre1 = p1;
				p1 = p1->next;
				pre1 = NULL;
				free(pre1);
			}
		}
		else {
			if (p1->next == NULL) {
				break;
			}
			else {
				pre1 = p1;
				p1 = p1->next;
			}
		}
	}


	/*ektupwsh*/
	ptr1 = airlines_p;
	p1 = airlines_p->p_root;
	printf("Airline%d=", i);
	while (p1 != NULL) {
		printf("<%d:%d> ", p1->pId, airlines_p->aId);
		p1 = p1->next;
	}
	printf("\n");
	ptr1 = ptr1->next;
	i++;

	while (ptr1 != airlines_p) {
		p1 = ptr1->p_root;
		printf("Airline%d=", i);
		while (p1 != NULL) {
			printf("<%d:%d> ", p1->pId, ptr1->aId);
			p1 = p1->next;
		}
		printf("\n");
		ptr1 = ptr1->next;
		i++;
	}

    return 1;
}


/**
 * @brief Partition airplanes
 *
 * @param aId         The airline id
 *
 * @return 1 on success
 *         0 on failure
 */
int partition_airplanes(int aId1) {
	_airlines_l *ptr1 = airlines_p;
	_airlines_l *ptr2 = airlines_p;
	_airlines_l *pre = NULL;
	_airplane *p1 = NULL;
	_airplane *p2 = NULL;
	_airplane *new = NULL;
	_airplane *new1 = NULL;
	int i = 1;
	int z = 0;
	int a = 1;

	if (airlines_p->aId == aId1) {
		pre = airlines_p->prev;
		p1 = airlines_p->p_root;
	}
	else {
		pre = ptr1;
		ptr1 = ptr1->next;

		while (ptr1 != airlines_p && ptr1->aId != aId1) {
			pre = ptr1;
			ptr1 = ptr1->next;
		}
		p1 = ptr1->p_root;
	}

	while (p1 != NULL) {
		new = create_airplanenode(p1->pId, p1->dest, p1->depart_time);

		/*pros ta empros*/
		while (z < i) {
			if (z == 0) ptr2 = ptr1->next;
			else if (z > 0) ptr2 = ptr2->next;

			if (ptr2->aId == aId1) ptr2 = ptr2->next;
			z++;
		}
		p2 = ptr2->p_root;

		if (p2 == NULL) {
			new = ptr2->p_root;
		}
		if (new->pId < p2->pId) {
			new->next = p2;
			ptr2->p_root = new;
		}
		else {
			while (p2->next != NULL && new->pId > p2->next->pId) {
				p2 = p2->next;
			}
			new->next = p2->next;
			p2->next = new;
		}
		ptr1->p_root = p1->next;
		free(p1);

		if (ptr1->p_root == NULL) break;
		else {
			p1 = ptr1->p_root;
			z = 0;
		}

		/*pros ta pisw*/
		new1 = create_airplanenode(p1->pId, p1->dest, p1->depart_time);


		while (z < i) {
			if (z == 0) ptr2 = ptr1->prev;
			else if (z > 0) ptr2 = ptr2->prev;

			if (ptr2->aId == aId1) ptr2 = ptr2->prev;
			z++;
		}
		p2 = ptr2->p_root;		

		if (p2 == NULL) {
			new1 = ptr2->p_root;
		} 
		else if (new1->pId < p2->pId) {
			new1->next = p2;
			ptr2->p_root = new1;
		}
		else {
			while (p2->next != NULL && new1->pId > p2->next->pId) {
				p2 = p2->next;
			}
			new1->next = p2->next;
			p2->next = new1;
		}
		ptr1->p_root = p1->next;
		free(p1);

		if (ptr1->p_root == NULL) break;
		else {
			p1 = ptr1->p_root;
			z = 0;
		}
		i++;
	}

	if (ptr1->aId == airlines_p->aId) {
		airlines_p = ptr1->next;
		ptr1 = NULL;
		free(ptr1);
		pre->next = airlines_p;
		airlines_p->prev = pre;

	}
	else {
		ptr1 = ptr1->next;
		free(ptr1->prev);
		pre->next = ptr1;
		ptr1->prev = pre;
	}

	ptr1 = airlines_p;
	p1 = airlines_p->p_root;
	printf("Airline%d=", a);
	while (p1 != NULL) {
		printf("<%d:%d> ", p1->pId, airlines_p->aId);
		p1 = p1->next;
	}
	printf("\n");
	ptr1 = ptr1->next;
	a++;

	while (ptr1 != airlines_p) {
		p1 = ptr1->p_root;
		printf("Airline%d=", a);
		while (p1 != NULL) {
			printf("<%d:%d> ", p1->pId, ptr1->aId);
			p1 = p1->next;
		}
		printf("\n");
		ptr1 = ptr1->next;
		a++;
	}
    return 1;
}


/**
 * @brief Travel
 *
 * @param dest         Destination
 * @param timestamp    Departure time
 *
 * @return 1 on success
 *         0 on failure
 */
int travel(int dest, int timestamp) {
	_flights_l *head = destTable[dest].flight_p;
	_flights_l *ptr;
	_flights_l *sentinel = create_sentinelnode();

	head = destTable[dest].flight_p;
	ptr = head;
		while (ptr != destTable[dest].sentinel_p && ptr->depart_time <= timestamp) {
			ptr = ptr->next;
		}
		while (ptr != destTable[dest].sentinel_p && ptr->depart_time > timestamp) {
			printf("<%d,%d> ", ptr->pId, ptr->depart_time);
			ptr = ptr->next;
		}

    return 1;
}


/**
 * @brief Print airlines
 *
 * @return 1 on success
 *         0 on failure
 */
int print_airlines() {
	_airlines_l* ptr = airlines_p;
	_airplane *ptr2 = NULL;
	int i = 0;

	if (airlines_p == NULL) return 0;
	
	printf("Airline%d: %d\n", i + 1, ptr->aId);
	printf("\tAirplane%d = ", i + 1);
	ptr2 = ptr->p_root;

	while (ptr2 != NULL) {
		printf("<%d>", ptr2->pId);
		ptr2 = ptr2->next;
	}
	printf("\n");
	ptr = ptr->next;
	i++;

	while (ptr!= airlines_p) {
		printf("Airline%d = %d\n", i+1, ptr->aId);
		printf("\tAirplane%d = ", i+1);
		ptr2 = ptr->p_root;

		while (ptr2 != NULL) {
			printf("<%d>", ptr2->pId);
			ptr2 = ptr2->next;
		}
		printf("\n");
		ptr = ptr->next;
		i++;
	}

    return 1;
}

/**
 * @brief Print destinations
 *
 * @return 1 on success
 *         0 on failure
 */
int print_destinations() {
	_flights_l *head;
	_flights_l *ptr3;
	int i = 0;

	for (i = 0; i < MAX_DEST; i++) {
		printf("Destinations%d= ", i + 1);

		head = destTable[i].flight_p;
		ptr3 = head;

		while (ptr3!= destTable[i].sentinel_p) {
			printf("<%d,%d> ", ptr3->pId, ptr3->depart_time);
			ptr3 = ptr3->next;
		}
		printf("\n");
	}

    return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    return 1;
}
