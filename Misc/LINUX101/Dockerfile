# Use a lightweight Ubuntu base image, e.g., the latest LTS version
FROM ubuntu:20.04

# Avoid prompts during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Update and upgrade Ubuntu packages
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends sudo && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create a new user 'shiba' without a password
RUN adduser --disabled-password --gecos "" shiba

# Copy the flag file to the created directory
# Ensure you have the file in your context when building the Docker image
COPY flag /home/shiba/flag

# Set permissions for all files in the flag folder
RUN chmod 600 /home/shiba/flag/*

# Set SUID bit on grep
RUN chmod u+s $(which grep)

# Ensure everything is owned by root but readable or executable by others as necessary
RUN chown root:root /home/shiba/flag && \
    chmod 755 /home/shiba

# Add a hint for the challenge
RUN echo 'Shiba found a special tool. It looks normal but can open secret doors. Look close at tools. Find the special one.' > /home/shiba/README

# Switch to the 'shiba' user
USER shiba

# Set the working directory to shiba's home directory
WORKDIR /home/shiba

# Define the default command to run an interactive shell
CMD ["/bin/bash"]
