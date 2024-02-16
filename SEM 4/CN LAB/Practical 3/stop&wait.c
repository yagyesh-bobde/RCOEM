/* STOP AND WAIT PROTOCOL (Alternating-Bit-Protocol) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define PACKET_SIZE 20
#define TIMEOUT_SEC 3

typedef struct Packet {
    int seq_num;
    bool is_ack;
    char data[PACKET_SIZE];
} Packet;

void send_packet(Packet packet) {
    printf("Sending packet with sequence number %d...\n", packet.seq_num);
    // Simulate transmission delay
    sleep(1);
}

Packet receive_packet() {
    Packet packet;
    // Simulate packet loss
    if (rand() % 10 > 2) {
        printf("Packet lost!\n");
        packet.seq_num = -1;
    } else {
        printf("Packet received!\n");
        packet.seq_num = rand() % 2;  //returns 0 or 1
        packet.is_ack = true;  
        sprintf(packet.data, "ACK%d", packet.seq_num); //If successful, it returns the total number of characters written excluding null-character appended in the string, in case of failure a negative number is returned.
    }
    // Simulate transmission delay
    sleep(1);
    return packet;
}

int main() {
    srand(time(NULL));
    Packet packet_to_send;
    Packet received_packet;
    bool waiting_for_ack = false;
    int next_seq_num = 0;
    while (true) {
        if (!waiting_for_ack) {
            // Generate packet to send
            packet_to_send.seq_num = next_seq_num;
            packet_to_send.is_ack = false;
            sprintf(packet_to_send.data, "Packet %d", next_seq_num);
            // Send packet
            send_packet(packet_to_send);
            // Set waiting_for_ack to true and start timeout timer
            waiting_for_ack = true;
            time_t start_time = time(NULL);
            while (difftime(time(NULL), start_time) < TIMEOUT_SEC) {
                // Check for incoming packet
                received_packet = receive_packet();
                if (received_packet.seq_num == next_seq_num && received_packet.is_ack) {
                    printf("ACK received for packet %d\n", next_seq_num);
                    waiting_for_ack = false;
                    next_seq_num = (next_seq_num + 1) % 2;
                    break;
                }
            }
            if (waiting_for_ack) {
                // Timeout occurred
                printf("Timeout occurred for packet %d\n", next_seq_num);
            }
        } else {
            // Check for incoming packet
            received_packet = receive_packet();
            if (received_packet.seq_num == next_seq_num && received_packet.is_ack) {
                printf("ACK received for packet %d\n", next_seq_num);
                waiting_for_ack = false;
                next_seq_num = (next_seq_num + 1) % 2;
            }
        }
    }
    return 0;
}