FROM debian

RUN apt-get update && apt-get install -y \
    gcc \
    libfcgi-dev \
    spawn-fcgi \
    && rm -rf /var/lib/apt/lists

COPY ./server.c ./home/server.c
COPY ./run.sh ./home/run.sh

WORKDIR /home/

RUN gcc -c server.c -o server.o \ 
    && gcc server.o -lfcgi -o server.out \
    && chmod +x run.sh

RUN groupadd -g 1000 appgroup && useradd -u 1000 -g appgroup -m appuser
USER appuser

ENTRYPOINT ["/home/run.sh"]