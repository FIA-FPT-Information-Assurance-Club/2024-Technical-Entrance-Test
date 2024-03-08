# Use an official PHP runtime as a parent image
FROM php:7.2-apache

# Set the working directory in the container to /var/www/html
WORKDIR /var/www/html

# Copy the current directory contents into the container at /var/www/html
COPY src /var/www/html/

# Open port 80 for the Apache web server
EXPOSE 80

# Use the default production configuration
RUN mv "$PHP_INI_DIR/php.ini-production" "$PHP_INI_DIR/php.ini"

# Enable Apache mod_rewrite
RUN a2enmod rewrite

# By default start up Apache in the foreground, override with /bin/bash for interative.
CMD [ "apache2-foreground" ]