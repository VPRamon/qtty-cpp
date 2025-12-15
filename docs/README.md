# Documentation

This directory contains user and contributor documentation for qtty-cpp.

## Index

| Document | Purpose |
|----------|---------|
| [README](../README.md) | Project overview and quick start |
| [Quick Reference](QUICK_REFERENCE.md) | One-page usage reference |
| [Architecture](architecture.md) | Architecture, layering, code generation |
| [API Reference](api/quantities.md) | API reference for `Quantity<UnitTag>` |
| [Build and Testing](build-and-testing.md) | Build instructions, testing, troubleshooting |
| [Extending Units](extending-units.md) | Adding units and regenerating headers |

## Suggested Reading Order

- Using the library: `../README.md`, then `api/quantities.md`
- Building and running tests: `build-and-testing.md`
- Understanding internals: `architecture.md`
- Adding units: `extending-units.md`

## Common Tasks

- Build the project: `build-and-testing.md#quick-start`
- Troubleshoot build failures: `build-and-testing.md#troubleshooting`
- Understand conversions: `architecture.md#data-flow-for-conversions`
- Review exception types: `api/quantities.md#exception-types`
- Add a new unit: `extending-units.md#step-by-step-guide`

## Documentation Maintenance

- Keep links relative so the docs work in forks and offline copies.
- Keep code examples minimal and consistent with the current API.
- Prefer plain ASCII punctuation and avoid decorative symbols and emoji.
