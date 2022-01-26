import socket

def menu():
    print('---------------------')
    print('Welcom to jetson TX2')
    print('---------------------')
    print('0. STOP')
    print('1. UP')
    print('2. DOWN')
    print('3. LEFT')
    print('4. RIGHT')
    print('5. APPLE')
    print('6. BANANA')
    print('7. BICYCLE')
    print('8. DOG')
    print('9. TRUCK')
    print('---------------------')

def input_key(key):
    if key == '0':
        return 'stop'
    elif key == '1':
        return 'up'
    elif key == '2':
        return 'down'
    elif key == '3':
        return 'left'
    elif key == '4':
        return 'right'
    elif key == '5':
        return 'apple'
    elif key == '6':
        return 'banana'
    elif key == '7':
        return 'bicycle'
    elif key == '8':
        return 'dog'
    elif key == '9':
        return 'truck'


# 서버의 주소입니다. hostname 또는 ip address를 사용할 수 있습니다.
HOST = 'localhost'
# HOST = '222.106.22.71'
# 서버에서 지정해 놓은 포트 번호입니다. 
# PORT = 9998       
PORT = 1234       

if __name__ == "__main__":
    # 소켓 객체를 생성합니다. 
    # 주소 체계(address family)로 IPv4, 소켓 타입으로 TCP 사용합니다.  
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


    # 지정한 HOST와 PORT를 사용하여 서버에 접속합니다. 
    client_socket.connect((HOST, PORT))
    try:
        while True:
            menu()
            key = input('Input: ')
            str = input_key(key)
            # 메시지를 전송합니다. 
            client_socket.sendall(str.encode())

    except KeyboardInterrupt:
        # 소켓을 닫습니다.
        client_socket.close()