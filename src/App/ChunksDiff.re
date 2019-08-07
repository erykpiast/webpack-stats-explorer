open Compare.Chunks;

module ChunksDiff =
  GenericDiff.Make({
    type a = chunk;

    let componentName = "ChunksDiff";
    let getName = chunk =>
      switch (chunk) {
      | Summary(chunk) => chunk.name
      | ModifiedSummary(chunk) => chunk.name
      };
  });

let make = ChunksDiff.make;
type props = ChunksDiff.props;