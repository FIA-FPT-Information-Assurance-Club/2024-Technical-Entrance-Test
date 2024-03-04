# Use a lightweight Ubuntu base image, e.g., the latest LTS version
FROM ubuntu:20.04

# Avoid prompts during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Update and upgrade Ubuntu packages
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends sudo openssh-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create SSH directory and update SSH configuration to listen on port 2222
RUN mkdir /var/run/sshd && \
    echo 'Port 2222' >> /etc/ssh/sshd_config && \
    # Disable root login over SSH
    echo 'PermitRootLogin no' >> /etc/ssh/sshd_config && \
    echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config

# Create a new user 'shiba' without a password
RUN adduser --disabled-password --gecos "" shiba

# Set password for shiba user
RUN echo 'shiba:shiba' | chpasswd

# Copy the flag file to the created directory
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

# Expose the SSH port
EXPOSE 2222

# Use the ENTRYPOINT to start the SSH daemon
USER root
ENTRYPOINT ["/usr/sbin/sshd", "-D"]