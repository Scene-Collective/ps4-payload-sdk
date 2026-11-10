FROM --platform=linux/amd64 ubuntu:22.04

# Set environment variable to disable interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools and clean up apt cache to reduce image size
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      binutils \
      build-essential \
      gcc \
      make && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory for the SDK
WORKDIR /lib/ps4-payload-sdk

# Copy the PS4 SDK source code into the container
COPY libPS4 /lib/ps4-payload-sdk/libPS4

# Build the PS4 SDK using make
RUN make -C /lib/ps4-payload-sdk/libPS4

# Set environment variable for the SDK path
ENV PS4SDK=/lib/ps4-payload-sdk

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
