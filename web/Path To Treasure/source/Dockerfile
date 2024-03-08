FROM python:3.10-slim-bullseye

USER root

WORKDIR /app
COPY . .

RUN adduser --shell /bin/bash ctf
USER ctf
RUN pip3 install --no-cache-dir flask

CMD ["python3", "app.py"]