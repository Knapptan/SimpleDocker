FROM debian

RUN apt-get update && apt-get install -y nginx \
    && rm -rf /var/lib/apt/lists
COPY ./nginx.conf /etc/nginx/nginx.conf

RUN groupadd -g 1000 appgroup && useradd -u 1000 -g appgroup -m appuser
USER appuser

ENTRYPOINT ["nginx", "-g", "daemon off;"]