type connection;

type configObj;

[@bs.obj]
external makeConfigObj :
  (
    ~host: string=?,
    ~port: int=?,
    ~user: string=?,
    ~password: string=?,
    ~database: string=?,
    unit
  ) =>
  configObj =
  "";

[@bs.module "mysql"] [@bs.val]
external createConnection : configObj => connection = "";

let createConnection =
    (~host=?, ~port=?, ~user=?, ~password=?, ~database=?, ()) =>
  createConnection(
    makeConfigObj(~host?, ~port?, ~user?, ~password?, ~database?, ())
  );

type error = {
  .
  "code": string,
  "fatal": bool,
  "message": string
};

type mysqlError = Js.Nullable.t(error);

type results;

type fields;

type result = {
  results,
  fields
};

type response = Js.Result.t(result, error);

[@bs.send]
external query :
  (connection, string, (mysqlError, results, fields) => unit) => unit =
  "query";

let query = (conn, queryStr, callback: response => unit) =>
  query(conn, queryStr, (error, results, fields) =>
    switch (Js.Nullable.to_opt(error)) {
    | None => callback(Js.Result.Ok({results, fields}))
    | Some(err) => callback(Js.Result.Error(err))
    }
  );

[@bs.send] external connect : connection => unit = "";

[@bs.send] external endConnection : connection => unit = "end";
