FROM nginx
WORKDIR /home/
# Create a user and group with a specific UID and GID
RUN groupadd -g 1000 appgroup && useradd -u 1000 -g appgroup -m appuser
# Set the user as the default
USER appuser
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c .
COPY ./run.sh .
RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    touch /var/run/nginx.pid; \
    rm -rf /var/lib/apt/lists
ENTRYPOINT ["sh", "./run.sh"]
HEALTHCHECK NONE
