import zmq
import socket

context = zmq.Context()

# 🔹 Socket PUB pour envoyer mute/unmute
pub_socket = context.socket(zmq.PUB)
pub_socket.bind("tcp://*:5555")  # Écoute sur le port 5555

# 🔹 Socket REQ-REP pour gérer l’état des élèves
rep_socket = context.socket(zmq.REP)
rep_socket.bind("tcp://*:5556")  # Écoute les demandes d'état

print("🔵 Serveur en attente des commandes Qt...")

while True:
    # 🔹 Vérifie si Qt envoie une commande
    try:
        message = rep_socket.recv_string(flags=zmq.NOBLOCK)  # Vérifie si Qt envoie un message
        print(f"📩 Commande reçue de Qt : {message}")

        # 🔹 Envoie la commande à tous les élèves
        pub_socket.send_string(message)
        rep_socket.send_string("OK")

    except zmq.Again:
        pass  # Aucune commande reçue
