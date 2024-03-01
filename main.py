import asyncio
import socket
import time
from drukarnia_api import Search

async def get_read_num():
    search = Search()

    async with search:
        search_res = await search.find_author('penrose')
        penrose = search_res[0]
        await penrose.collect_data()

        return penrose.data.get('readNum')

def send_read_num(read_num):
    while True:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(('192.168.50.7', 9050))
            s.sendall(read_num.encode())
            s.close()
            print("ReadNum sent successfully:", read_num)
            break
        except Exception as e:
            print("Error occurred while sending ReadNum:", e)
            print("Retrying in 10 seconds...")
            time.sleep(10)

async def main():
    while True:
        read_num = await get_read_num()
        send_read_num(str(read_num))
        await asyncio.sleep(10)

if __name__ == '__main__':
    asyncio.run(main())
