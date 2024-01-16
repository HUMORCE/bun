// @known-failing-on-windows: 1 failing
import { expect, test } from "bun:test";
import { resolve } from "path";
import MyPNG from "./test-png.png";

test("png import", () => {
  expect(MyPNG).toBe(resolve(__dirname, "./test-png.png"));
});
