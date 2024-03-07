FROM php:7.2-apache

# Install necessary packages
RUN apt-get update && apt-get install -y zip cron

# Copy source files and a secret flag
WORKDIR /var/www/html
COPY ./src .
COPY flag.txt /a68d30b_secret.txt

# Configure permissions
RUN chown -R root:www-data /var/www/html && \
    chmod 750 /var/www/html && \
    find . -type f -exec chmod 640 {} \; && \
    find . -type d -exec chmod 750 {} \; && \
    chmod +t -R /var/www/html/

# Setup cron job to clean /tmp every 10 minutes
RUN echo "*/10 * * * * /bin/rm -rf /tmp/*" | crontab -

# Create a script to start cron and Apache
RUN echo "#!/bin/bash\nservice cron start\napache2-foreground" > /start.sh && \
    chmod +x /start.sh

CMD ["/start.sh"]