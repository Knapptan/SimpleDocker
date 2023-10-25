FROM nginx
WORKDIR /home/
RUN apt-get update && apt-get install -y gcc libfcgi-dev spawn-fcgi
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c .
COPY ./run.sh .
ENTRYPOINT ["sh", "./run.sh"]