FROM ubuntu:latest
COPY --from=ghcr.io/astral-sh/uv:latest /uv /uvx /bin/

ENV VENV_DIR=/venv

RUN apt-get update && apt-get install -y --no-install-recommends \
    curl ca-certificates cmake make libfl2 wget bzip2

RUN uv python install 3.12 && uv venv -p 3.12 ${VENV_DIR} && uv --directory ${VENV_DIR} pip install xmltodict

CMD ["bash"]
