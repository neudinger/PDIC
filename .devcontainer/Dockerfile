FROM debian:bullseye-slim as devroot

LABEL MAINTAINER="Barre Kevin"
LABEL VERSION="1.0"
LABEL SRC=https://github.com/neudinger/ \
    DESCRIPTION="PDIC Container"


ARG USERNAME=pdi
ARG USER_UID=1000
ENV PATH /bin:/sbin:/usr/bin:$PATH
ENV DEBIAN_FRONTEND=noninteractive

ENV LOGGING_LEVEL=INFO
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8 HOME=/home/${USERNAME}
ENV PATH=/usr/sbin:/bin:/sbin:/usr/bin:${HOME}/.local/bin:/usr/local/bin
ENV USER_NAME=$USERNAME
ENV CONDA_DIR=/opt/conda
ENV PATH=${CONDA_DIR}/bin:${PATH}

RUN set -eux && \
    apt update -y && apt install -y --no-install-recommends \
    curl ca-certificates tar build-essential sudo git binutils-gold \
    libtool libtool-bin zlib1g-dev libssl-dev \
    libncursesw5 libpthread-stubs0-dev \
    clang-format clang-tidy clang-tools clang clangd libc++-dev \
    libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev \
    libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python-clang
RUN update-alternatives --install "/usr/bin/ld" "ld" `which ld.gold` 10

SHELL ["/bin/bash", "-c"]

USER root

WORKDIR $HOME

RUN groupadd --gid $USER_UID $USERNAME; \
	useradd -s /bin/bash --uid $USER_UID --gid $USER_UID -m $USERNAME

RUN echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME
RUN chmod 0440 /etc/sudoers.d/$USERNAME
RUN apt-get purge -y --auto-remove -o APT::AutoRemove::RecommendsImportant=false

WORKDIR ${HOME}

ENV APP_HOME ${HOME}/app/
RUN set -eux;\
    mkdir -p ${APP_HOME} && \
    chown -R ${USERNAME}:${USERNAME} ${HOME}

SHELL ["/bin/bash", "-c"]

WORKDIR $HOME
# MiniConda

RUN set -eux && \
    curl --progress-bar -L \
    https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-$(uname)-$(uname -m).sh -o Miniforge3.sh && \
    bash Miniforge3.sh -b -p ${CONDA_DIR} && \
    rm Miniforge3.sh

RUN set -eux && \
    curl --progress-bar -L \
    https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-pypy3-$(uname)-$(uname -m).sh -o Mambaforge.sh && \
    bash Mambaforge.sh -b -u ${CONDA_DIR} && \
    rm Mambaforge.sh

COPY requirement.yml ${HOME}

RUN set -eux; \
    conda env create --name pdic-env -f requirement.yml && \
    conda init bash && \
    rm requirement.yml

ENV PATH=$HOME/miniconda/envs/pdic-env/bin:${PATH}
RUN echo "PATH=${PATH}" >> ~/.bashrc
WORKDIR $APP_HOME
SHELL ["/bin/bash", "-c"]
RUN echo "conda activate pdic-env" >> ~/.bashrc
COPY --chown=${USER_NAME}:${USER_NAME} entrypoint.sh ${HOME}
RUN chown -R ${USER_NAME}:${USER_NAME} /home
ENTRYPOINT ["/bin/bash", "/home/pdi/entrypoint.sh"]
CMD ["bash"]
# USER root
USER $USERNAME