FROM ubuntu:latest

RUN apt update ; \
    DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
        make \
        sudo \
        build-essential \
        cmake \
        cpputest \
        ; \
    apt autoremove -y; apt clean; rm /var/lib/apt/lists/* -r ; \
    rm -rf /usr/share/man/* ; \
    rm -rf /tmp/* /var/tmp/*

RUN adduser builder --disabled-password --gecos "" --shell /bin/bash ; \
    echo "builder ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers ; \
    sed -i "s/^#force_color_prompt=.*/force_color_prompt=yes/" /home/builder/.bashrc ; \
    touch /home/builder/.bash_login

COPY docker/bashrc /home/builder/.bashrc

ENV GCC_COLORS=error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01
ENV PS1="\[\033[01;32m\]\u\[\033[00m\]: \[\033[01;34m\]\w\[\033[00m\] \$"

# Add entry task
COPY docker/entry.sh /
ENTRYPOINT ["/entry.sh"]
RUN chmod +x /entry.sh
RUN mkdir /src

RUN update-alternatives --install /bin/sh sh /bin/bash 40

USER builder

