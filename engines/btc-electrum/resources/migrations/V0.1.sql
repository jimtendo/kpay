CREATE TABLE migrations (
  name text PRIMARY KEY
);

CREATE TABLE wallets (
  id integer PRIMARY KEY AUTOINCREMENT,
  name text NOT NULL,
  type text NOT NULL,
  key text NOT NULL
); 
