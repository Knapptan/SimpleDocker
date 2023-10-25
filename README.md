# Part 1. Готовый докер

Написание докер образа для собственного веб сервера
В начале нужно разобраться с уже готовым докер образом для сервера.
Выбор пал на **nginx**.

## Взять официальный докер образ с **nginx** и выкачать его при помощи `docker pull`

Для этого предварительно неоходимо установить сам докер на компьютер 

`docker pull nginx`

![docker pull nginx](./images/1.png)

## Проверить наличие докер образа через `docker images`

![docker images](./images/2.png)

## Запустить докер образ через `docker run -d [image_id|repository]`

` docker run -d bc649bab30d1 `
![docker run](./images/3.png)

## Проверить, что образ запустился через `docker ps`

![docker ps](./images/4.png)

## Посмотреть информацию о контейнере через `docker inspect [container_id|container_name]`

![docker inspect](./images/5.png)

## По выводу команды определить и поместить в отчёт размер контейнера, список замапленных портов и ip контейнера

Для удобства воспользуемся  `docker inspect` вместе с `grep`

### Размер контейнера

`docker inspect d250fcff3e45 --size | grep Size`

![docker inspect size](./images/6.png)

### Список замапленных портов

`docker inspect d250fcff3e45 --size | grep Ports -A 2`

![docker inspect size 2](./images/7.png)

### ip контейнера

`docker inspect d250fcff3e45 --size | grep IPAddress`

![docker inspect size 3](./images/8.png)

## Остановить докер образ через `docker stop [container_id|container_name]`

`docker stop d250fcff3e45`

![docker stop](./images/9.png)

## Проверить, что образ остановился через `docker ps`

![docker ps 2](./images/10.png)

##### Запустить докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*

`docker run -d -p 80:80 -p 443:443 nginx`

![docker run 2](./images/11.png)

## Проверить, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**

![GH localhost:80](./images/12.png)

## Перезапустить докер контейнер через `docker restart [container_id|container_name]`

Узнаем имя контейнера `docker ps` - `ecstatic_swirles`

`docker restart ecstatic_swirles`

![docker restart](./images/13.png)

## Проверить любым способом, что контейнер запустился

Исппользуем `docker ps`

![docker ps 3](./images/14.png)


# Part 2. Операции с контейнером

Докер образ и контейнер готовы. 
Теперь конфигурации **nginx** и отображение статуса страницы.

## Прочитать конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*

`docker exec ecstatic_swirles cat /etc/nginx/nginx.conf`

![docker exec](./images/15.png)

## Создать на локальной машине файл *nginx.conf*

`docker exec ecstatic_swirles cat /etc/nginx/nginx.conf >> nginx.conf`

![docker exec 2](./images/16.png)

## Настроить в нем по пути */status* отдачу страницы статуса сервера **nginx**

![docker nginx.conf](./images/17.png)

## Скопировать созданный файл *nginx.conf* внутрь докер образа через команду `docker cp`

`docker cp src/nginx.conf ecstatic_swirles:/etc/nginx`

![docker cp](./images/18.png)

## Перезапустить **nginx** внутри докер образа через команду *exec*

`docker exec ecstatic_swirles nginx -s reload`

![docker exec 3](./images/19.png)

## Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**

![GH localhost:80/status](./images/20.png)

## Экспортировать контейнер в файл *container.tar* через команду *export*

`docker export ecstatic_swirles > container.tar`

![docker export](./images/21.png)

## Остановить контейнер

`docker stop ecstatic_swirles`

![docker stop](./images/22.png)

## Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры

`docker rmi -f nginx`

![docker rmi](./images/23.png)

## Удалить остановленный контейнер

`docker rm ecstatic_swirles`

![docker rm](./images/24.png)

## Импортировать контейнер обратно через команду *import*

`docker import -c 'cmd ["nginx", "-g", "daemon off;"]' container.tar nginx`

![docker import](./images/25.png)

## Запустить импортированный контейнер

`docker run -d -p 80:80 -p 443:443 8ec9687630df`

![docker run 2](./images/26.png)

## Проверить, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**

![GH localhost:80/status 2](./images/27.png)

# Part 3. Мини веб-сервер

Cвой сервер.

## Написать мини сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`

![main.c](./images/28.png)

## Запустить написанный мини сервер через *spawn-fcgi* на порту 8080

Запускаем с портами 80 и 81 ак как ебхдимо проксировать с 81 порта на 80 

`docker run -d -p 80:80 -p 81:81 nginx`

![docker run 3](./images/29.png)
![docker ps 3](./images/31.png)

## Написать свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*

![nginx.conf 2](./images/30.png)

## Положить файл *nginx.conf* по пути *./nginx/nginx.conf* (это понадобится позже)

Конфигурация прописана, осталось добавить файлы в контейнер 

`docker cp nginx.conf admiring_elgamal:/etc/nginx`

`docker exec ecstatic_swirles nginx -s reload

![nginx.conf cp](./images/32.png)

`docker cp server.c admiring_elgamal:/home`

![server cp](./images/33.png)

И также у нашего контейнера нет компилятора чтобы запустить написанный мини сервер через *spawn-fcgi*

По этому обновляем 

`docker exec admiring_elgamal apt-get update`

![update](./images/34.png)

Скачиваем нужные пакеты gcc и spawn-fcgi

`docker exec admiring_elgamal apt-get install -y gcc libfcgi-dev spawn-fcgi`

![install gcc spawn-fcgi](./images/35.png)

Компилируем 

`docker exec admiring_elgamal gcc -o server /home/server.c -lfcgi`

![gcc spawn-fcgi server](./images/36.png)

Запускаем 

`docker exec admiring_elgamal spawn-fcgi -p 8080 ./server`

![spawn-fcgi server](./images/37.png)

## Проверить, что в браузере по *localhost:81* отдается написанная вами страничка

![GH localhost:81](./images/38.png)

# Part 4. Свой докер

## Пишем свой докер образ, который:
### 1) собирает исходники мини сервера на FastCgi из Части 3
### 2) запускает его на 8080 порту
### 3) копирует внутрь образа написанный *./nginx/nginx.conf*
### 4) запускает **nginx**.

Для такого рода сборки создаем докер файл 

В нем у нас будет набор команд для обновления, скачивания пакетов и копирования файлов из директории сборки или можно прописать относительный/абсолютный путь до файлов

![Dockerfile](./images/39.png)

Далее копируем файлы в директорию сборки(в моем случае src) из прошлой части - nginx.conf, server.c

Также нам нужен скрипт который скомпилирует и запустит нужный нам файл для сервера и примет конфигурации nginx - run.sh

![run.sh](./images/40.png)

## Собираем написанный докер образ через `docker build` при этом указав имя и тег

`docker build -t knapptan:1 .` где имя  - мой ник, а тег 1

![docker build](./images/41.png)

## Проверяем через `docker images`, что все собралось корректно

![docker images](./images/42.png)

## Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки *./nginx* внутрь контейнера по адресу, где лежат конфигурационные файлы **nginx**'а 

`docker run -d -p 80:81 -v /Users/knapptan/Desktop/Projects/DO5_SimpleDocker-1/src/nginx.conf:/etc/nginx/nginx.conf -d knapptan:1 bash`

![docker run 3](./images/43.png)

## Проверить, что по localhost:80 доступна страничка написанного мини сервера

![GH localhost:80 2](./images/44.png)

## Дописываем в *./nginx/nginx.conf* проксирование странички */status*, по которой надо отдавать статус сервера **nginx**

![nginx.conf 3](./images/45.png)

## Перезапустить докер образ
*Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер образа должен обновиться самостоятельно без лишних действий*

`docker restart heuristic_euclid`

![docker restart 3](./images/46.png)

## Проверить, что теперь по *localhost:80/status* отдается страничка со статусом **nginx**

![GH localhost:80/status 3](./images/47.png)

# Part 5. **Dockle**

## Просканировать образ из предыдущего задания через `dockle [image_id|repository]`

`dockle knapptan:1`

![dockle](./images/48.png)

Ошибки которые нобходимо исправить: 
FATAL   - CIS-DI-0010: Do not store credential in environment variables/files
FATAL   - DKL-DI-0005: Clear apt-get caches
WARN    - CIS-DI-0001: Create a user for the container

Для этого правим докерфайл: 
добавим user - добавляю  конце чтобы не было конфликтов при вызове команд, 
удалим после настройки файлы которые уже не нужны - кеш списка пакетов.
И сменим nginx на debian - базовый образ так как nginx хранит ENV-ключ NGINX_GPGKEY,
который не проходит проверку dockle.
Можно использовать Docker Secrets или другие методы для хранения конфиденциальных данных.
В данном случае просто не используем эти данные.

## Исправить образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений

![dockle 2](./images/49.png)

# Part 6. Базовый **Docker Compose**

## Написать файл *docker-compose.yml*, с помощью которого:

### 1) Поднять докер контейнер из Части 5 _(он должен работать в локальной сети, т.е. не нужно использовать инструкцию **EXPOSE** и мапить порты на локальную машину)_
### 2) Поднять докер контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера
## Замапить 8080 порт второго контейнера на 80 порт локальной машины

![docker-compose.yml](./images/50.png)

## Остановить все запущенные контейнеры

![docker-compose ps](./images/51.png)

## Собрать и запустить проект с помощью команд `docker-compose build` и `docker-compose up`

`docker-compose build`

![docker-compose build](./images/52.png)

`docker-compose up -d`

Флаг -d в команде docker-compose up означает "в фоновом режиме" (detached)

![docker-compose up](./images/53.png)

`docker ps`

Проверяем првильность работы

![docker ps](./images/54.png)

## Проверить, что в браузере по *localhost:80* отдается написанная вами страничка, как и ранее

![GH localhost:80 4](./images/55.png)