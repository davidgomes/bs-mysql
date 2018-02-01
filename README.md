# MySQL.js Bindings for Reason/Bucklescript

This repository contains in-progress Reason/Bucklescript bindings for [mysql](https://github.com/mysqljs/mysql).

## Example

```ocaml
let conn = Mysql.createConnection(~host="127.0.0.1", ~port=3306, ~user="root", ());

Mysql.query(conn, "SHOW DATABASES", result => {
  switch (result) {
  | Ok(results) => Js.log(results.results)
  | Error(err) => Js.log(err##message)
  }
});

Mysql.endConnection(conn);
```

## Installation

1. Install the bindings using `npm install --save bs-mysql`
2. Add the bindings to `bsconfig.json`:

```json
{
  "bs-dependencies": ["bs-mysql"]
}
```

## Build

```
npm run build
```

## Build + Watch

```
npm run start
```

## Current State & Todo

The API is still very incomplete. Use at your own risk, contributions are welcome!
